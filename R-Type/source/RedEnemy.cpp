#include "RedEnemy.h"
#include "Application.h"


RedEnemy::RedEnemy(const char* pTextureFileName, const char* pTextureRollUp, const char* pTextureRollDown, const char* pTextureFlipped, float a_width, float a_height, float a_posX, float a_posY, float a_speed) :Enemy(pTextureFileName, pTextureRollUp, pTextureRollDown, pTextureFlipped, a_width, a_height, a_posX, a_posY, a_speed)
{
	m_fTurnPoint = a_posY;
	m_animEndTime = 0.1f;
}

RedEnemy::~RedEnemy()
{
}

void RedEnemy::Update(float a_fDeltaTime)
{

	Enemy::Update(a_fDeltaTime);

	if (m_onScreen)
	{
		Oscillate();
		m_y += m_velocity[1] * a_fDeltaTime;
	}	

	UG::Application::MoveSprite(m_SpriteID[m_currentSprite], m_x, m_y);

	//Set boundaries according to the new position
	SetEdges(width, height);
	
}

void RedEnemy::Oscillate()
{
	if (m_y >= (m_fTurnPoint + 70) || m_y <= (m_fTurnPoint - 70))
	{
		m_velocity[1] *= -1;
	}
}