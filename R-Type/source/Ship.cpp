#include "Ship.h"
#include "Application.h"

Ship::Ship(const char* pTextureFileName, const char* pTextureRollUp, const char* pTextureRollDown, const char* pTextureDead, float a_width, float a_height, const float &a_fBoundaryX, const float &a_fBoundaryY) : Entity(pTextureFileName, pTextureRollUp, pTextureRollDown, pTextureDead, a_width, a_height, 102.f, 390.4f, 0.f)
{
	m_AnimationTimer = 0;
	m_CurrentAnimClip = 0;

	m_dead = false;

	SetPosition(102.f, 390.4f);
	SetVelocity(20, 20);
	SetBoundary(a_fBoundaryX,a_fBoundaryY);
	SetControls(UG::KEY_UP, UG::KEY_DOWN, UG::KEY_LEFT, UG::KEY_RIGHT, UG::KEY_LEFT_CONTROL);
}

Ship::~Ship()
{

}

void Ship::Update(float a_fDeltaTime)
{
	m_AnimationTimer += a_fDeltaTime;
	m_currentSprite = 0;

		Movement(a_fDeltaTime);

	//Set edge boundaries according to the new position
		SetEdges(width, height);
}

void Ship::Movement(float a_fDeltaTime)
{
	float fHalfY = height * 0.5f;
	float fHalfX = width * 0.5f;
	float currentY = m_y;
	float currentX = m_x;

	m_velocity[0] = 0.f;
	m_velocity[1] = 0.f;

	m_currentSprite = 0;

	//Up Key is down
	if (UG::Application::IsKeyDown(m_Keys[0]))
	{
		m_velocity[1] += 200.f;
		m_currentSprite = 1;
	}
	//Down Key is down
	if (UG::Application::IsKeyDown(m_Keys[1]))
	{
		m_velocity[1] += -200.f;
		m_currentSprite = 2;
	}
	//Left Key is down
	if (UG::Application::IsKeyDown(m_Keys[2]))
	{
		m_velocity[0] += -200.f;
	}
	//Right Key is down
	if (UG::Application::IsKeyDown(m_Keys[3]))
	{
		m_velocity[0] += 200.f;
	}

	currentY += m_velocity[1] * a_fDeltaTime;
	currentX += m_velocity[0] * a_fDeltaTime;

	if (!(currentY >((m_fYBoundary - 31) - fHalfY) || currentY < 76 + fHalfY))
	{
		m_y = currentY;
	}
	else
	{
		Die();
	}
	if (!(currentX >(m_fXBoundary - fHalfX) || currentX < fHalfX))
	{
		m_x = currentX;
	}

	UG::Application::MoveSprite(m_SpriteID[m_currentSprite], m_x, m_y);
}

void Ship::Reset()
{
	Entity::Reset();
	m_dead = false;
}

void Ship::SetBoundary(const float& a_x, const float& a_y)
{
	m_fXBoundary = a_x;
	m_fYBoundary = a_y;
}

void Ship::SetControls(unsigned int a_up, unsigned int a_down, unsigned int a_left, unsigned int a_right, unsigned int a_fire)
{
	m_Keys[0] = a_up;
	m_Keys[1] = a_down;
	m_Keys[2] = a_left;
	m_Keys[3] = a_right;
	m_Keys[4] = a_fire;
}

unsigned int Ship::getKey(int key)
{
	return m_Keys[key];
}

void Ship::Die() 
{
	m_dead = true;
}

bool Ship::isDead()
{
	return m_dead;
}