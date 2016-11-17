#include "Blast.h"
#include "Application.h"


Blast::Blast(const char* pTextureFileName, const char* pTextureMed, const char* pTextureMed2, const char* pTextureCharged, float a_width, float a_height, float a_x, float a_y) : Entity (pTextureFileName, pTextureMed, pTextureMed2, pTextureCharged, a_width, a_height, a_x, a_y, 0.f, 64, 96, 160, 20, 24, 28)
{
	
}

Blast::~Blast()
{
}

void Blast::Update(float a_fDeltaTime)
{
	float currentY = m_y;
	float currentX = m_x;

	currentX += m_velocity[0] * a_fDeltaTime;

	m_x = currentX;
	m_y = currentY;

if (currentX > m_fXBoundary)
	{
		Reset();
		m_velocity[0] = 0.f;
	}

Entity::Update(a_fDeltaTime);

}

void Blast::SetBoundary(const float& a_x, const float& a_y)
{
	m_fXBoundary = a_x;
	m_fYBoundary = a_y;
}

void Blast::SetSprite(int spriteID)
{
	m_currentSprite = spriteID;
}

int Blast::GetSprite()
{
	return m_currentSprite;
}

void Blast::Reset()
{
	m_x = -10;
	m_y = 0;
	m_velocity[0] = 0.f;
	m_currentSprite = 0;
}

