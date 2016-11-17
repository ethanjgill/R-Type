#ifndef __RType_H_
#define __RType_H_

#include "Application.h"
#include <glm/glm.hpp>

class Ship;
class Background;
class Obstacle;
class RedEnemy;
class BrownEnemy;
class Blast;
class Menu;

// Derived application class that wraps up all globals neatly
class RType : public UG::Application
{
public:

	RType();
	virtual ~RType();

	void InitialiseObs();
	void InitialiseEnms();

	void CheckBullet(int &bulletNo);

protected:

	virtual bool onCreate(int a_argc, char* a_argv[]);
	virtual void onUpdate(float a_deltaTime);
	virtual void onDraw();
	virtual void onDestroy();

	void CreateGame();
	void UpdateGame(float a_deltaTime);
	void DrawGame();

	void RestartGame();

private:
	int m_iScreenWidth;
	int m_iScreenHeight;

	int m_Score;

	int m_iGameSpeed;

	int m_availableBullet;
	bool m_isButtonDown;

	float m_Charge;

	bool m_Playing;
	bool m_Splash;
	bool m_Scores;

	float m_SplashTime;

	int m_Lives;

	Ship* m_pShip1;

	Background* m_Background;

	Obstacle* m_Obstacles[29];

	RedEnemy* m_RedEnemy[45];
	BrownEnemy* m_BroEnemy[10];

	Blast* m_bullet[4];

	Menu* m_MainMenu;
	Background* m_SplashScreen;

	Background* m_UI;
	Background* m_ChargeBar;
	Background* m_LifeIcons[2];
};

#endif // __RType_H_