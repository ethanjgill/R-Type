#ifndef __Enemy_H__
#define __Enemy_H__

#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(const char* pTextureFileName, const char* pTextureRollUp, const char* pTextureRollDown, const char* pTextureFlipped, float a_width, float a_height, float a_posX, float a_posY, float a_speed);
	virtual ~Enemy();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();

	void Die();
	bool isDead();

	void SetOnScreen(bool a_onScreen);
	bool onScreen();

	virtual void Reset();

protected:

	float m_animationEnd;
	float m_animEndTime;

	bool m_Dead;
	bool m_onScreen;
};

#endif