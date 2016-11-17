#ifndef __Ship_H__
#define __Ship_H__

#include "Entity.h"

class Ship : public Entity
{
public:
	Ship(const char* pTextureFileName, const char* pTextureRollUp, const char* pTextureRollDown, const char* pTextureDead, float a_width, float a_height, const float &a_fBoundaryX, const float &a_fYBoundary);
	virtual ~Ship();

	virtual void Update(float a_fDeltaTime);
	void Reset();

	void SetBoundary(const float& a_x, const float& a_y);

	void SetControls(unsigned int a_up, unsigned int a_down, unsigned int a_left, unsigned int a_right, unsigned int a_fire);

	void Movement(float a_fDeltaTime);

	unsigned int getKey(int key);

	void Die();
	bool isDead();

private:

	float m_fXBoundary;
	float m_fYBoundary;

	bool m_dead;

	float m_AnimationTimer;
	int m_CurrentAnimClip;

	unsigned int m_Keys[4];
};

#endif