#include "Menu.h"
#include "Application.h"

Menu::Menu(const char* pTextureFileName, float a_width, float a_height)
{
	m_TextureID = UG::Application::CreateSprite(pTextureFileName, a_width, a_height);
	m_Selection = 0;

	UG::Application::MoveSprite(m_TextureID, a_width * 0.5f, a_height * 0.5f);
}

Menu::~Menu()
{
	UG::Application::DestroySprite(m_TextureID);
}

void Menu::Update(float a_fDeltaTime)
{
	if (UG::Application::IsKeyDown(UG::KEY_1))
	{
		m_Selection = 1;
	}
	else if (UG::Application::IsKeyDown(UG::KEY_2))
	{
		m_Selection = 2;
	}
	else if (UG::Application::IsKeyDown(UG::KEY_3))
	{
		m_Selection = 3;
	}
}

void Menu::Draw()
{
	UG::Application::DrawSprite(m_TextureID);
}

int Menu::GetSelection()
{
	return m_Selection;
}

void Menu::SetSelection(int a_selection)
{
	m_Selection = a_selection;
}

bool Menu::isActive()
{
	return m_active;
}