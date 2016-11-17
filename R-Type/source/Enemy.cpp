#include "Enemy.h"
#include "Application.h"


Enemy::Enemy(const char* pTexture0, const char* pTexture1, const char* pTexture2, const char* pTexture3, float a_width, float a_height, float a_posX, float a_posY, float a_speed) : Entity(pTexture0, pTexture1, pTexture2, pTexture3, a_width, a_height, a_posX, a_posY, a_speed)
{
	m_SpriteID[0] = UG::Application::CreateSprite(pTexture1, a_width, a_height, true);
	m_SpriteID[1] = UG::Application::CreateSprite(pTexture0, a_width, a_height, true);
	m_SpriteID[2] = UG::Application::CreateSprite(pTexture2, a_width, a_height, true);
	m_SpriteID[3] = UG::Application::CreateSprite(pTexture3, a_width, a_height, true);

	SetVelocity(-a_speed, a_speed);

	m_animationEnd = 0;

	m_Dead = false;
	m_onScreen = false;

	SetEdges(width, height);
}

Enemy::~Enemy()
{
}

void Enemy::Update(float a_fDeltaTime)
{

	if (m_velocity[0] != -75)
	{
		m_animationEnd += a_fDeltaTime;

		if (m_animationEnd > m_animEndTime)
		{
			if (m_currentSprite < 3)
			{
				m_currentSprite += 1;
			}
			else
			{
				m_currentSprite = 0;
			}

			m_animationEnd = 0;
		}
	}
	else
	{
		m_currentSprite = 1;
	}

	m_x += m_velocity[0] * a_fDeltaTime;

	UG::Application::MoveSprite(m_SpriteID[m_currentSprite], m_x, m_y);

	//Set boundaries according to the new position
	SetEdges(width, height);

}

void Enemy::Draw()
{
	UG::Application::DrawSprite(m_SpriteID[m_currentSprite]);
}

void Enemy::Die()
{
	m_Dead = true;
}

bool Enemy::isDead()
{
	return m_Dead;
}

void Enemy::SetOnScreen(bool a_onScreen)
{
	m_onScreen = a_onScreen;
}

bool Enemy::onScreen()
{
	return m_onScreen;
}

void Enemy::Reset()
{
	Entity::Reset();
	m_Dead = false;
	m_onScreen = false;
}