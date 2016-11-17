#include "Ball.h"
#include "Application.h"


Ball::Ball(const char* pTextureFileName, float a_width, float a_height)
{
	m_SpriteID = UG::Application::CreateSprite(pTextureFileName, a_width, a_height, true);
	m_fSize = a_width;

	SetPosition(0.f, 0.f);
	SetVelocity(100, 100);
}

Ball::~Ball() 
{
	UG::Application::DestroySprite(m_SpriteID);
}

void Ball::Update(float a_fDeltaTime) 
{
	m_x += m_velocityX * a_fDeltaTime;
	m_y += m_velocityY * a_fDeltaTime;

	float fHalfSize = m_fSize * 0.5f;

	if (m_x > (m_fXBoundary - fHalfSize) || m_x < fHalfSize)
	{
		m_velocityX *= -1;
	}
	if (m_y > (m_fYBoundary - fHalfSize) || m_y < fHalfSize)
	{
		m_velocityY *= -1;
	}
	UG::Application::MoveSprite(m_SpriteID, m_x, m_y);
}

void Ball::Draw()
{
	UG::Application::DrawSprite(m_SpriteID);
}

void Ball::Reset()
{
	m_x = 512.f;
	m_y = 390.f;
}

void Ball::GetPosition(float& a_x, float& a_y) const
{
	a_x = m_x;
	a_y = m_y;
}

void Ball::SetPosition(const float& a_x, const float& a_y)
{
	m_x = a_x;
	m_y = a_y;
}

void Ball::SetVelocity(int a_x, int a_y)
{
	m_velocityX = a_x;
	m_velocityY = a_y;
}

void Ball::SetBoundary(const float& a_x, const float& a_y)
{
	m_fXBoundary = a_x;
	m_fYBoundary = a_y;
	Reset();
}