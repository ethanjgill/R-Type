#include "Entity.h"
#include "Application.h"


Entity::Entity(const char* pTexture0, const char* pTexture1, const char* pTexture2, const char* pTexture3, float a_width, float a_height, float a_posX, float a_posY, float a_speed, float a_width1, float a_width2, float a_width3, float a_height1, float a_height2, float a_height3)
{
	m_SpriteID[0] = UG::Application::CreateSprite(pTexture0, a_width, a_height, true);
	if (!(pTexture1 == "" && pTexture2 == "" && pTexture3 == ""))
	{
		if (!(a_width1 == 0.f && a_height1 == 0.f))
		{
			m_SpriteID[1] = UG::Application::CreateSprite(pTexture1, a_width1, a_height1, true);
		}
		else
		{
			m_SpriteID[1] = UG::Application::CreateSprite(pTexture1, a_width, a_height, true);
		}
		if (!(a_width2 == 0.f && a_height2 == 0.f))
		{
			m_SpriteID[2] = UG::Application::CreateSprite(pTexture2, a_width2, a_height2, true);
		}
		else
		{
			m_SpriteID[2] = UG::Application::CreateSprite(pTexture2, a_width, a_height, true);
		}
		if (!(a_width3 == 0.f && a_height3 == 0.f))
		{
			m_SpriteID[3] = UG::Application::CreateSprite(pTexture3, a_width3, a_height3, true);
		}
		else
		{
			m_SpriteID[3] = UG::Application::CreateSprite(pTexture3, a_width, a_height, true);
		}
	}
	else
	{
		m_SpriteID[1] = UG::Application::CreateSprite(pTexture0, a_width, a_height, true);
		m_SpriteID[2] = UG::Application::CreateSprite(pTexture0, a_width, a_height, true);
		m_SpriteID[3] = UG::Application::CreateSprite(pTexture0, a_width, a_height, true);
	}

	m_currentSprite = 0;

	SetSize(a_width, a_height);

	SetVelocity(-a_speed, 0);

	SetPosition(a_posX, a_posY);

	m_OriginalX = a_posX;
	m_OriginalY = a_posY;
}

Entity::~Entity()
{
	UG::Application::DestroySprite(m_SpriteID[0]);
	UG::Application::DestroySprite(m_SpriteID[1]);
	UG::Application::DestroySprite(m_SpriteID[2]);
	UG::Application::DestroySprite(m_SpriteID[3]);
}

void Entity::Update(float a_fDeltaTime)
{
	m_x += m_velocity[0] * a_fDeltaTime;
	m_y += m_velocity[1] * a_fDeltaTime;

	UG::Application::MoveSprite(m_SpriteID[m_currentSprite], m_x, m_y);

	//Set boundaries according to the new position
	m_boundaryX[0] = m_x - (width * 0.5f);
	m_boundaryX[1] = m_x + (width * 0.5f);

	m_boundaryY[0] = m_y - (height * 0.5f);
	m_boundaryY[1] = m_y + (height * 0.5f);
}

void Entity::Draw()
{
	UG::Application::DrawSprite(m_SpriteID[m_currentSprite]);
}

void Entity::SetVelocity(float a_XVelocity, float a_YVelocity)
{
	m_velocity[0] = a_XVelocity;
	m_velocity[1] = a_YVelocity;
}

void Entity::GetVelocity(float& a_XVelocity, float& a_YVelocity) const
{
	a_XVelocity = m_velocity[0];
	a_YVelocity = m_velocity[1];
}

void Entity::GetPosition(float& a_x, float& a_y) const
{
	a_x = m_x;
	a_y = m_y;
}

void Entity::SetPosition(const float& a_x, const float& a_y)
{
	m_x = a_x;
	m_y = a_y;
}

void Entity::GetSize(float& a_w, float& a_h) const
{
	a_w = width;
	a_h = height;
}

void Entity::SetSize(const float& a_w, const float& a_h)
{
	width = a_w;
	height = a_h;
}

void Entity::GetEdges(float(&a_x)[2], float(&a_y)[2]) const
{
	a_x[0] = m_boundaryX[0];
	a_x[1] = m_boundaryX[1];

	a_y[0] = m_boundaryY[0];
	a_y[1] = m_boundaryY[1];
}

void Entity::SetEdges(const float& a_w, const float& a_h)
{
	m_boundaryX[0] = m_x - (a_w * 0.5f);
	m_boundaryX[1] = m_x + (a_w * 0.5f);

	m_boundaryY[0] = m_y - (a_h * 0.5f);
	m_boundaryY[1] = m_y + (a_h * 0.5f);
}

void Entity::Reset()
{
	m_x = m_OriginalX;
	m_y = m_OriginalY;
	m_currentSprite = 0;
}