#ifndef __Menu_H__
#define __Menu_H__

class Menu
{
public:
	Menu(const char* pTextureFileName, float a_width, float a_height);
	~Menu();

	void Update(float a_fDeltaTime);
	void Draw();

	int GetSelection();
	void SetSelection(int a_selection);
	bool isActive();

private:

	int m_Selection;
	unsigned int m_TextureID;
	bool m_active;
};

#endif