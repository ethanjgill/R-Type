#include "Application.h"
#include "RType.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include "windows.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>
#include "Ship.h"
#include "Background.h"
#include "Obstacle.h"
#include "RedEnemy.h"
#include "BrownEnemy.h"
#include "Enemy.h"
#include "Blast.h"
#include "Menu.h"

//This is an example of a complex #define that obfuscates the entry point of the application
//APPLICATION_ENTRY can be found in Application.h it is a define that hides the main() entry point
//of the application. This is done so that each application can be called and run in the same manner
//it is not something that needs to be fully understood until much later in the CGP course.

APPLICATION_ENTRY(RType);

//A default constructor for RType() and it's accompanying destructor ~FrameworkTest()
//Any initialisation could be placed in here, these are empty for now. They are here to ensure that
//the correct application creation sequence is called.
RType::RType(){}
RType::~RType(){}

//onCreate is a function that is called once on the creation of the application. This is where items 
//that will last for the duration of the application should be created. EG Player sprites
bool RType::onCreate(int a_argc, char* a_argv[])
{
	//A variable controlling the speed at which the background and obstacles move.
	m_iGameSpeed = 75;

	m_availableBullet = -1;
	m_isButtonDown = false;
	m_Charge = 0.f;
	m_Lives = 2;
	m_SplashTime = 0.f;

	Application::SetBackgroundColor(UG::SColour(0x00, 0x00, 0x00, 0xFF));
	Application::AddFont("./fonts/invaders.fnt");
	Application::GetScreenSize(m_iScreenWidth, m_iScreenHeight);

	m_Playing = false;
	m_Splash = true;

	m_MainMenu = new Menu("./images/Menu.png", m_iScreenWidth, m_iScreenHeight);
	m_SplashScreen = new Background("./images/Splash.png", m_iScreenWidth, m_iScreenHeight, m_iScreenWidth * 0.5f, m_iScreenHeight * 0.5f, false);
	m_SplashScreen->SetVelocity(0.f);

	CreateGame();

	return true;
}

//onUpdate - this function is called each frame of the application, the a_deltaTime variable is a floating point value
//that gives the length of time that has passed since the previous frame was rendered.
void RType::onUpdate(float a_deltaTime)
{
	if (m_Splash)
	{
		m_SplashScreen->Update(a_deltaTime);
		m_SplashTime += a_deltaTime;
		if (m_SplashTime >= 10)
		{
			m_Splash = false;
		}
	}

	if (m_Scores)
	{
		if (IsKeyDown(UG::KEY_ESCAPE))
		{
			m_Scores = false;
		}
	}

	if (!m_Playing)
	{
		m_MainMenu->Update(a_deltaTime);
		
		if (m_MainMenu->GetSelection() == 1)
		{
			m_Lives = 3;
			m_Playing = true;
			m_MainMenu->SetSelection(0);
			RestartGame();
		}
		else if (m_MainMenu->GetSelection() == 2)
		{
			//DisplayScores
			m_Scores = true;
			m_MainMenu->SetSelection(0);
		}
		else if (m_MainMenu->GetSelection() == 3)
		{
			destroy();
		}
	}
	else
	{
		if (m_pShip1->isDead())
		{
			RestartGame();
		}
		UpdateGame(a_deltaTime);
	}	
}

void RType::CheckBullet(int &bulletNo)
{
	float bulletX;
	float bulletY;

	int i = 0;

	bulletNo = -1;

	while (bulletNo == -1 && i < 4)
	{
		m_bullet[i]->GetPosition(bulletX, bulletY);

		if (bulletX == -10 && bulletY == 0)
		{
			bulletNo = i;
		}
		i++;
	}
}

//onDraw is called each frame after onUpdate has been called
//this is where any rendering should be carried out
void RType::onDraw()
{
	Application::ClearScreen();

	if (m_Splash)
	{
		m_SplashScreen->Draw();

	}
	else
	{
		if (!m_Playing)
		{
			if (!m_Scores)
			{
				m_MainMenu->Draw();
			}
			else
			{
				//Display Scores From File
				std::string Scores[10];

				for (int i = 0; i <= 9; i++)
				{
					Scores[i] = "";
				}

				std::ifstream m_ScoresFile("Scores.txt");

				for (int i = 0; m_ScoresFile.good() && i < 10; i++)
				{
					std::getline(m_ScoresFile, Scores[i]);
				}

				for (int i = 9; i >= 0; i-=1)
				{
					DrawString(Scores[i].c_str(), m_iScreenWidth * 0.5f - Scores[i].length()*7.5f, (m_iScreenHeight*(0.9f - ((10-i)*0.06f))) + 13.f, 1.f, UG::SColour(0xFF, 0xFF, 0xFF, 0xFF));
				}
				m_ScoresFile.close();
			}
		}
		else
		{
			DrawGame();
		}
	}
	
}

void RType::InitialiseObs()
{
	float bottomRow = 77;
	float topRow = (((m_iScreenHeight + 48)*0.5f) + 239) - 29;
	

	//Creating the obstacles and positioning them according to the background image with the same velocity so that they will move with the background.
	m_Obstacles[0] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Small.png","","","", 128, 32, 32, bottomRow + 16, m_iGameSpeed);
	m_Obstacles[1] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Large.png","","","", 128, 64, 564, bottomRow + 32, m_iGameSpeed);
	m_Obstacles[2] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Small.png", "", "", "", 128, 32, 692, bottomRow + 16, m_iGameSpeed);
	m_Obstacles[3] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Small.png", "", "", "", 128, 32, 1458, bottomRow + 16, m_iGameSpeed);
	m_Obstacles[4] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Large.png", "", "", "", 128, 64, 1713, bottomRow + 32, m_iGameSpeed);
	m_Obstacles[5] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Small.png", "", "", "", 128, 32, 2737, bottomRow + 16, m_iGameSpeed);

	m_Obstacles[6] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Turbine.png", "", "", "", 224, 160, 3073, bottomRow + 80, m_iGameSpeed);
	m_Obstacles[7] = new Obstacle("./images/Obstacles/Ripped/Obstacle Top Turbine.png", "", "", "", 224, 160, 3073, topRow - 80, m_iGameSpeed);

	m_Obstacles[8] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Small.png", "", "", "", 128, 32, 3633, bottomRow + 16, m_iGameSpeed);
	m_Obstacles[9] = new Obstacle("./images/Obstacles/Ripped/Obstacle Top Small.png", "", "", "", 128, 32, 3633, topRow - 16, m_iGameSpeed);
	m_Obstacles[10] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Large.png", "", "", "", 128, 64, 3761, bottomRow + 32, m_iGameSpeed);
	m_Obstacles[11] = new Obstacle("./images/Obstacles/Ripped/Obstacle Top Large.png", "", "", "", 128, 64, 3761, topRow - 32, m_iGameSpeed);

	m_Obstacles[12] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Ramp Left.png", "", "", "", 124, 48, 4399, bottomRow + 24, m_iGameSpeed);
	m_Obstacles[13] = new Obstacle("./images/Obstacles/Ripped/Obstacle Top Ramp Left.png", "", "", "", 124, 48, 4399, topRow - 24, m_iGameSpeed);
	m_Obstacles[14] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Ramp Right.png", "", "", "", 124, 48, 4659, bottomRow + 24, m_iGameSpeed);
	m_Obstacles[15] = new Obstacle("./images/Obstacles/Ripped/Obstacle Top Ramp Right.png", "", "", "", 124, 48, 4659, topRow - 24, m_iGameSpeed);

	m_Obstacles[16] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Large.png", "", "", "", 128, 64, 5041, bottomRow + 32, m_iGameSpeed);
	m_Obstacles[17] = new Obstacle("./images/Obstacles/Ripped/Obstacle Top Small.png", "", "", "", 128, 32, 5041, topRow - 16, m_iGameSpeed);

	m_Obstacles[18] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Small.png", "", "", "", 128, 32, 5553, bottomRow + 16, m_iGameSpeed);
	m_Obstacles[19] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Large.png", "", "", "", 128, 64, 5681, bottomRow + 32, m_iGameSpeed);
	m_Obstacles[20] = new Obstacle("./images/Obstacles/Ripped/Obstacle Top Large.png", "", "", "", 128, 64, 5681, topRow - 32, m_iGameSpeed);

	m_Obstacles[21] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Claw.png", "", "", "", 384, 160, 6065, bottomRow + 80, m_iGameSpeed);
	m_Obstacles[22] = new Obstacle("./images/Obstacles/Ripped/Obstacle Top Claw.png", "", "", "", 384, 160, 6065, topRow - 80, m_iGameSpeed);

	m_Obstacles[23] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Small.png", "", "", "", 128, 32, 6449, bottomRow + 16, m_iGameSpeed);
	m_Obstacles[24] = new Obstacle("./images/Obstacles/Ripped/Obstacle Top Small.png", "", "", "", 128, 32, 6449, topRow - 16, m_iGameSpeed);

	m_Obstacles[25] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Small.png", "", "", "", 128, 32, 7090, bottomRow + 16, m_iGameSpeed);
	m_Obstacles[26] = new Obstacle("./images/Obstacles/Ripped/Obstacle Top Small.png", "", "", "", 128, 32, 7090, topRow - 16, m_iGameSpeed);
	m_Obstacles[27] = new Obstacle("./images/Obstacles/Ripped/Obstacle Bottom Large.png", "", "", "", 128, 64, 7218, bottomRow + 32, m_iGameSpeed);
	m_Obstacles[28] = new Obstacle("./images/Obstacles/Ripped/Obstacle Top Large.png", "", "", "", 128, 64, 7218, topRow - 32, m_iGameSpeed);
}

void RType::InitialiseEnms()
{

	float bottomRow = 77;
	float topRow = (((m_iScreenHeight + 48)*0.5f) + 239) - 29;
	
	//Red Enemies initialised in small groups of where they will appear.
		m_RedEnemy[0] = new RedEnemy("./images/Red Enemy Level.png", "./images/Red Enemy Up.png", "./images/Red Enemy Down.png", "./images/Red Enemy Flipped.png", 42, 28, 1100 + (0 * 75), m_iScreenHeight * 0.71f, 150.f);
		m_RedEnemy[1] = new RedEnemy("./images/Red Enemy Level.png", "./images/Red Enemy Up.png", "./images/Red Enemy Down.png", "./images/Red Enemy Flipped.png", 42, 28, 1100 + (1 * 75), m_iScreenHeight * 0.68f, 150.f);

	for (int i = 2; i < 4; i++)
	{
		m_RedEnemy[i] = new RedEnemy("./images/Red Enemy Level.png", "./images/Red Enemy Up.png", "./images/Red Enemy Down.png", "./images/Red Enemy Flipped.png", 42, 28, 1100 + (i * 75), m_iScreenHeight * 0.7f, 150.f);
	}

	for (int i = 4; i < 8; i++)
	{
		m_RedEnemy[i] = new RedEnemy("./images/Red Enemy Level.png", "./images/Red Enemy Up.png", "./images/Red Enemy Down.png", "./images/Red Enemy Flipped.png", 42, 28, 1220 + (i * 75), m_iScreenHeight * 0.7f, 140.f);
	}

	for (int i = 8; i < 11; i++)
	{
		m_RedEnemy[i] = new RedEnemy("./images/Red Enemy Level.png", "./images/Red Enemy Up.png", "./images/Red Enemy Down.png", "./images/Red Enemy Flipped.png", 42, 28, 2500 + (i * 75), m_iScreenHeight * 0.8f, 190.f);
	}

	for (int i = 11; i < 23; i++)
	{
		m_RedEnemy[i] = new RedEnemy("./images/Red Enemy Level.png", "./images/Red Enemy Up.png", "./images/Red Enemy Down.png", "./images/Red Enemy Flipped.png", 42, 28, 1900 + (i * 75), m_iScreenHeight * 0.65f, 100.f);
	}

	for (int i = 23; i < 27; i++)
	{
		m_RedEnemy[i] = new RedEnemy("./images/Red Enemy Level.png", "./images/Red Enemy Up.png", "./images/Red Enemy Down.png", "./images/Red Enemy Flipped.png", 42, 28, 4133 + (i * 50), m_iScreenHeight * 0.4f, 100.f);
	}

	for (int i = 27; i < 32; i++)
	{
		m_RedEnemy[i] = new RedEnemy("./images/Red Enemy Level.png", "./images/Red Enemy Up.png", "./images/Red Enemy Down.png", "./images/Red Enemy Flipped.png", 42, 28, 4600 + (i * 75), m_iScreenHeight * 0.5f, 100.f);
	}

	for (int i = 32; i < 38; i++)
	{
		m_RedEnemy[i] = new RedEnemy("./images/Red Enemy Level.png", "./images/Red Enemy Up.png", "./images/Red Enemy Down.png", "./images/Red Enemy Flipped.png", 42, 28, 5541 + (i * 75), m_iScreenHeight * 0.7f, 100.f);
	}

	for (int i = 38; i < 45; i++)
	{
		m_RedEnemy[i] = new RedEnemy("./images/Red Enemy Level.png", "./images/Red Enemy Up.png", "./images/Red Enemy Down.png", "./images/Red Enemy Flipped.png", 42, 28, 9990 + (i * 75), m_iScreenHeight * 0.5f, 100.f);
	}

	//Brown Enemies initialised.

	m_BroEnemy[0] = new BrownEnemy("./images/Brown Enemy #1.png", "./images/Brown Enemy #2.png", "./images/Brown Enemy #3.png", "./images/Brown Enemy #1.png", 64, 64, 1600, bottomRow + 32, m_iGameSpeed + 30);
	m_BroEnemy[1] = new BrownEnemy("./images/Brown Enemy #1.png", "./images/Brown Enemy #2.png", "./images/Brown Enemy #3.png", "./images/Brown Enemy #1.png", 64, 64, 1800, bottomRow + 96, m_iGameSpeed + 5);
	m_BroEnemy[2] = new BrownEnemy("./images/Brown Enemy #1.png", "./images/Brown Enemy #2.png", "./images/Brown Enemy #3.png", "./images/Brown Enemy #1.png", 64, 64, 3200, bottomRow + 32, m_iGameSpeed + 30);
	m_BroEnemy[3] = new BrownEnemy("./images/Brown Enemy #1 Flipped.png", "./images/Brown Enemy #2 Flipped.png", "./images/Brown Enemy #3 Flipped.png", "./images/Brown Enemy #1 Flipped.png", 64, 64, 1700, bottomRow + 32, m_iGameSpeed - 20);
	m_BroEnemy[4] = new BrownEnemy("./images/Brown Enemy #1.png", "./images/Brown Enemy #2.png", "./images/Brown Enemy #3.png", "./images/Brown Enemy #1.png", 64, 64, 3000, bottomRow + 32, m_iGameSpeed + 30);
	m_BroEnemy[5] = new BrownEnemy("./images/Brown Enemy #1.png", "./images/Brown Enemy #2.png", "./images/Brown Enemy #3.png", "./images/Brown Enemy #1.png", 64, 64, 3853, bottomRow + 64,  m_iGameSpeed + 5);
	m_BroEnemy[6] = new BrownEnemy("./images/Brown Enemy #1.png", "./images/Brown Enemy #2.png", "./images/Brown Enemy #3.png", "./images/Brown Enemy #1.png", 64, 64, 5529, bottomRow + 32, m_iGameSpeed + 30);
	m_BroEnemy[7] = new BrownEnemy("./images/Brown Enemy #1.png", "./images/Brown Enemy #2.png", "./images/Brown Enemy #3.png", "./images/Brown Enemy #1.png", 64, 64, 4529, bottomRow + 32, m_iGameSpeed);
	m_BroEnemy[8] = new BrownEnemy("./images/Brown Enemy #1.png", "./images/Brown Enemy #2.png", "./images/Brown Enemy #3.png", "./images/Brown Enemy #1.png", 64, 64, 5553, bottomRow + 64, m_iGameSpeed);
	m_BroEnemy[9] = new BrownEnemy("./images/Brown Enemy #1.png", "./images/Brown Enemy #2.png", "./images/Brown Enemy #3.png", "./images/Brown Enemy #1.png", 64, 64, 9490, bottomRow + 32, m_iGameSpeed + 30);
}

void RType::CreateGame()
{
	m_Background = new Background("./images/R-Type Level 1 Ripped BACKGROUND.png", 7710, 478, 3850.5f, ((m_iScreenHeight + 48)*0.5f), false);
	m_Background->SetVelocity(-m_iGameSpeed);

	m_UI = new Background("./images/UI.png", m_iScreenWidth, 45, m_iScreenWidth * 0.5f, 22.5f, false);
	m_UI->SetVelocity(0.f);

	m_ChargeBar = new Background("./images/ChargeBar.png", 200, 10, 367, 36, false);
	m_ChargeBar->SetVelocity(0.f);
	m_ChargeBar->SetSize(0,10);

	m_LifeIcons[0] = new Background("./images/Life.png", 12, 14, 23, 36, false);
	m_LifeIcons[0]->SetVelocity(0.f);

	m_LifeIcons[1] = new Background("./images/Life.png", 12, 14, 39, 36, false);
	m_LifeIcons[1]->SetVelocity(0.f);

	InitialiseObs();
	InitialiseEnms();

	//Creating the main player object with three main sprites that will be switched between when moving in runtime.
	m_pShip1 = new Ship("./images/ShipLevel.png", "./images/ShipRollUpFull.png", "./images/ShipRollDownFull.png", "./images/Explosion#5.png", 64, 28, m_iScreenWidth, m_iScreenHeight);

	m_bullet[0] = new Blast("./images/Blast.png", "./images/Blast Mid 1.png", "./images/Blast Mid 2.png", "./images/Blast Charged.png", 32, 8, -10, 0);
	m_bullet[1] = new Blast("./images/Blast.png", "./images/Blast Mid 1.png", "./images/Blast Mid 2.png", "./images/Blast Charged.png", 32, 8, -10, 0);
	m_bullet[2] = new Blast("./images/Blast.png", "./images/Blast Mid 1.png", "./images/Blast Mid 2.png", "./images/Blast Charged.png", 32, 8, -10, 0);
	m_bullet[3] = new Blast("./images/Blast.png", "./images/Blast Mid 1.png", "./images/Blast Mid 2.png", "./images/Blast Charged.png", 32, 8, -10, 0);

	m_bullet[0]->SetBoundary(m_iScreenWidth, m_iScreenHeight);
	m_bullet[1]->SetBoundary(m_iScreenWidth, m_iScreenHeight);
	m_bullet[2]->SetBoundary(m_iScreenWidth, m_iScreenHeight);
	m_bullet[3]->SetBoundary(m_iScreenWidth, m_iScreenHeight);
}

void RType::UpdateGame(float a_deltaTime)
{
	m_Background->Update(a_deltaTime);

	float backX, backY;
	m_Background->GetPosition(backX, backY);
	//When the player reaches the end, end the game and add 10000 to the score.
	if (backX < -4000)
	{
		m_Lives = 0;
		m_Score += 10000;
		RestartGame();
	}

	m_UI->Update(a_deltaTime);
	m_ChargeBar->Update(a_deltaTime);

	for (int i = 0; i < (m_Lives); i++)
	{
		m_LifeIcons[i]->Update(a_deltaTime);
	}

	//Updating each obstacle.
	for (int i = 0; i < 29; i++)
	{
		m_Obstacles[i]->Update(a_deltaTime);
	}

	//Update the Ship
	m_pShip1->Update(a_deltaTime);

	//Update each Red Enemy
	for (int i = 0; i < 45; i++)
	{
		if (!m_RedEnemy[i]->isDead())
		{
			float enmX, enmY;

			//If enemy is within the screen bounds, it must oscillate.
			m_RedEnemy[i]->GetPosition(enmX, enmY);
			if (enmX < m_iScreenWidth && enmX > 0)
			{
				m_RedEnemy[i]->SetOnScreen(true);
			}
			else
			{
				m_RedEnemy[i]->SetOnScreen(false);
			}

			m_RedEnemy[i]->Update(a_deltaTime);
		}
	}

	//Update each Brown Enemy
	for (int i = 0; i < 10; i++)
	{
		if (!m_BroEnemy[i]->isDead())
		{
			float enmX, enmY;

			//If enemy is within screen bounds, flag that it is onScreen.
			m_BroEnemy[i]->GetPosition(enmX, enmY);
			if (enmX < m_iScreenWidth && enmX > 0)
			{
				m_BroEnemy[i]->SetOnScreen(true);
			}
			else
			{
				m_BroEnemy[i]->SetOnScreen(false);
			}

			m_BroEnemy[i]->Update(a_deltaTime);
		}
	}

	float shipX[2];
	float shipY[2];

	float obsX[2];
	float obsY[2];

	float bulX[4][2];
	float bulY[4][2];

	m_pShip1->GetEdges(shipX, shipY);

	for (int i = 0; i < 4; i++)
	{
		m_bullet[i]->GetEdges(bulX[i], bulY[i]);
	}

	//Check each obstacle for collision detection with ship.
	for (int i = 0; i < 29; i++)
	{
		m_Obstacles[i]->GetEdges(obsX, obsY);

		//If the right of the ship is further than the left of the object in question,
		//the left of the ship is nearer than the right of the object,
		//the bottom of the ship is lower than the top of the object
		//and the top of the ship is higher than the bottom of the object,
		//then at least some part of the ship is intersecting the object and therefore the ship is destroyed.
		if (shipX[1] >= obsX[0] && shipX[0] <= obsX[1] && shipY[0] < obsY[1] && shipY[1] > obsY[0])
		{
			m_pShip1->Die();
			break;
		}

		//If bullet hits obstacle, reset bullet.
		for (int j = 0; j < 4; j++)
		{
			if (bulX[j][1] >= obsX[0] && bulX[j][0] <= obsX[1] && bulY[j][0] < obsY[1] && bulY[j][1] > obsY[0])
			{
				m_bullet[j]->Reset();
				break;
			}
		}
	}

	//Check each red enemy for collision detection with ship.
	for (int i = 0; i < 45; i++)
	{
		if (!m_RedEnemy[i]->isDead())
		{
			m_RedEnemy[i]->GetEdges(obsX, obsY);

			//If the right of the ship is further than the left of the object in question,
			//the left of the ship is nearer than the right of the object,
			//the bottom of the ship is lower than the top of the object
			//and the top of the ship is higher than the bottom of the object,
			//then at least some part of the ship is intersecting the object and therefore the ship is destroyed.
			if (shipX[1] >= obsX[0] && shipX[0] <= obsX[1] && shipY[0] < obsY[1] && shipY[1] > obsY[0])
			{
				m_pShip1->Die();
				break;
			}

			//Check collision with bullet. If so, kill enemy and reset bullet.
			for (int j = 0; j < 4; j++)
			{
				if (bulX[j][1] >= obsX[0] && bulX[j][0] <= obsX[1] && bulY[j][0] < obsY[1] && bulY[j][1] > obsY[0])
				{
					m_RedEnemy[i]->Die();
					m_Score += 200;

					//Charged blast goes through enemies
					if (m_bullet[j]->GetSprite()  < 2)
					{
						m_bullet[j]->Reset();
					}
					break;
				}
			}
		}
	}

	//Check each brown enemy for collision detection with ship.
	for (int i = 0; i < 10; i++)
	{
		if (!m_BroEnemy[i]->isDead())
		{
			m_BroEnemy[i]->GetEdges(obsX, obsY);

			//If the right of the ship is further than the left of the object in question,
			//the left of the ship is nearer than the right of the object,
			//the bottom of the ship is lower than the top of the obstacle
			//and the top of the ship is higher than the bottom of the obstacle,
			//then at least some part of the ship is intersecting the obstacle and therefore the ship is destroyed.
			if (shipX[1] >= obsX[0] && shipX[0] <= obsX[1] && shipY[0] < obsY[1] && shipY[1] > obsY[0])
			{
				m_pShip1->Die();
				break;
			}

			//Check collision with bullet. If so, kill enemy and reset bullet.
			for (int j = 0; j < 4; j++)
			{
				if (bulX[j][1] >= obsX[0] && bulX[j][0] <= obsX[1] && bulY[j][0] < obsY[1] && bulY[j][1] > obsY[0])
				{
					m_BroEnemy[i]->Die();
					m_Score += 400;

					//Charged blast goes through enemies
					if (m_bullet[j]->GetSprite() < 2)
					{
						m_bullet[j]->Reset();
					}
					break;
				}
			}
		}
	}

	//Shoot Key is down
	if (Application::IsKeyDown(m_pShip1->getKey(4)))
	{
		m_isButtonDown = true;
	}

	//If button is released, fire bullet
	if (!(Application::IsKeyDown(m_pShip1->getKey(4))) && m_isButtonDown == true)
	{
		float shipX, shipY;

		m_pShip1->GetPosition(shipX, shipY);

		CheckBullet(m_availableBullet);
		if (m_availableBullet != -1)
		{
			if (m_Charge >= 2000)
			{
				m_bullet[m_availableBullet]->SetSprite(3);
				m_bullet[m_availableBullet]->SetSize(160, 28);
			}
			else if (m_Charge >= 1500)
			{
				m_bullet[m_availableBullet]->SetSprite(2);
				m_bullet[m_availableBullet]->SetSize(96, 24);
			}
			else if (m_Charge >= 500)
			{
				m_bullet[m_availableBullet]->SetSprite(1);
				m_bullet[m_availableBullet]->SetSize(64, 20);
			}
			else
			{
				m_bullet[m_availableBullet]->SetSprite(0);
				m_bullet[m_availableBullet]->SetSize(32, 8);
			}
			m_bullet[m_availableBullet]->SetPosition(shipX, shipY);
			m_bullet[m_availableBullet]->SetVelocity(1000.f, 0.f);
		}

		m_Charge = 0.f;
		m_ChargeBar->SetSize(0, 10);
		m_isButtonDown = false;
	}
	else if (Application::IsKeyDown(m_pShip1->getKey(4)) && m_isButtonDown == true)
	{
		if (m_Charge < 2000)
		{
			m_Charge += 1000 * a_deltaTime;
			m_ChargeBar->SetSize(m_Charge / 10, 10);
		}
	}

	m_bullet[0]->Update(a_deltaTime);
	m_bullet[1]->Update(a_deltaTime);
	m_bullet[2]->Update(a_deltaTime);
	m_bullet[3]->Update(a_deltaTime);

	// quit our application when escape is pressed
	if (Application::IsKeyDown(UG::KEY_ESCAPE))
		destroy();
}

void RType::DrawGame()
{
	m_Background->Draw();
	m_UI->Draw();
	m_ChargeBar->Draw();

	for (int i = 0; i < (m_Lives); i++)
	{
		m_LifeIcons[i]->Draw();
	}

	std::string score = std::to_string(m_Score);
	char *ScoreChar = (char*)score.c_str();

	DrawString(ScoreChar, 259, 28, 0.5f);

	float obsX = 0;
	float obsY = 0;
	float obsW = 0;
	float obsH = 0;

	//Drawing each obstacle when on screen.
	for (int i = 0; i < 29; i++)
	{
		m_Obstacles[i]->GetPosition(obsX, obsY);
		m_Obstacles[i]->GetSize(obsW, obsH);

		//If obstacle is even partly on screen, draw it. If not, do not.
		if ((obsX - (obsW * 0.5f)) < m_iScreenWidth && (obsX + (obsW * 0.5f)) > 0 && (obsY - (obsH * 0.5f)) < m_iScreenHeight && (obsY + (obsH * 0.5f)) > 0)
		{
			m_Obstacles[i]->Draw();
		}
	}

	m_bullet[0]->Draw();
	m_bullet[1]->Draw();
	m_bullet[2]->Draw();
	m_bullet[3]->Draw();

	m_pShip1->Draw();

	//Draw each enemy that isn't dead.
	for (int i = 0; i < 45; i++)
	{
		if (!m_RedEnemy[i]->isDead() && m_RedEnemy[i]->onScreen())
		{
			m_RedEnemy[i]->Draw();
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (!m_BroEnemy[i]->isDead() && m_BroEnemy[i]->onScreen())
		{
			m_BroEnemy[i]->Draw();
		}
	}

	Application::SetFont("./fonts/invaders.fnt");
	DrawLine(0, 46, m_iScreenWidth, 46);
	Application::SetFont(nullptr);
}

void RType::RestartGame()
{
	if (m_Lives > 0)
	{
		m_pShip1->Reset();
		m_Background->Reset();

		for (int i = 0; i < 29; i++)
		{
			m_Obstacles[i]->Reset();
		}

		for (int i = 0; i < 45; i++)
		{
			m_RedEnemy[i]->Reset();
		}

		for (int i = 0; i < 10; i++)
		{
			m_BroEnemy[i]->Reset();
		}

		for (int i = 0; i < 4; i++)
		{
			m_bullet[i]->Reset();
		}

		m_Lives -= 1;
	}
	else
	{
		//Display Scores From File
		std::string Scores[10];
		int ScorePos;

		for (int i = 0; i < 10; i++)
		{
			Scores[i] = "";
		}

		std::ifstream m_ScoresFile;
		m_ScoresFile.open("Scores.txt");

		for (int i = 0; m_ScoresFile.good() && i < 10; i++)
		{
			std::getline(m_ScoresFile, Scores[i]);
		}

		m_ScoresFile.close();

		//figure out position of score in the array
		for (int i = 0; i < 10; i++)
		{
			if (m_Score > atoi(Scores[i].c_str()))
			{
				ScorePos = i;
			}
		}

		//push all scores below the new score down
		for (int i = 0; i < ScorePos; i++)
		{
			Scores[i] = Scores[i + 1];
		}

		//Put score in the appropriate place
		Scores[ScorePos] = std::to_string(m_Score);
		
		//loop through the scores and write them to the file.
		std::ofstream ScoresFile;
		ScoresFile.open("Scores.txt");
		for (int i = 0; i < 10; i++)
		{
			ScoresFile << Scores[i] << std::endl;
		}
		ScoresFile.close();

		m_Score = 0;

		m_Playing = false;
	}
}

//onDestroy - this will be called at the termination of the application. Any items which need to be
//deallocated should be done so in here. E.G things that were created in the onCreate function.
void RType::onDestroy()
{
	delete m_MainMenu;
	delete m_pShip1;
	delete m_Background;
	delete m_UI;
	delete m_ChargeBar;
	
	for (int i = 0; i < 29; i++)
	{
		delete m_Obstacles[i];
	}

	for (int i = 0; i < 45; i++)
	{
		delete m_RedEnemy[i];
	}

	for (int i = 0; i < 10; i++)
	{
		delete m_BroEnemy[i];
	}

	for (int i = 0; i < 4; i++)
	{
		delete m_bullet[i];
	}	
}