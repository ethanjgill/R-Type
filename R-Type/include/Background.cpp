#include "Background.h"
#include "Application.h"


Background::Background(const char* pTextureFileName, float a_width, float a_height, float a_posX, float a_posY, bool a_vertical)
{
	m_SpriteID = UG::Application::CreateSprite(pTextureFileName, a_width, a_height, true);
	width = a_width;
	height = a_height;
	m_verticalMotion = a_vertical;

	SetPosition(a_posX, a_posY);

	m_OriginalX = a_posX;
	m_OriginalY = a_posY;
}

Background::~Background()
{
	UG::Application::DestroySprite(m_SpriteID);
}

void Background::Update(float a_fDeltaTime)
{
	

	if (m_verticalMotion)
	{
		if (m_y + (height * 0.5f) < 0)
		{
		m_y = (height*0.5f) + (2 * height);
		}

		m_y += m_velocity * a_fDeltaTime;
	}
	else
	{
		if (m_x + (width * 0.5f) < 0)
		{
			m_x = (width*0.5f) + (2 * width);
		}

		m_x += m_velocity * a_fDeltaTime;
	}

	UG::Application::MoveSprite(m_SpriteID, m_x, m_y);
}

void Background::Draw()
{
//	if (m_y - (height * 0.5f) < height)
//	{
		UG::Application::DrawSprite(m_SpriteID);
//	}
}

void Background::SetVelocity(float a_velocity)
{
	m_velocity = a_velocity;
}

void Background::GetPosition(float& a_x, float& a_y) const
{
	a_x = m_x;
	a_y = m_y;
}

void Background::SetPosition(const float& a_x, const float& a_y)
{
	m_x = a_x;
	m_y = a_y;
}

void Background::SetSize(const float& a_w, const float& a_h)
{
	width = a_w;
	height = a_h;

	UG::Application::SetSpriteScale(m_SpriteID, width, height);
}

void Background::Reset()
{
	m_x = m_OriginalX;
	m_y = m_OriginalY;
}