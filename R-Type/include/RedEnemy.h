#ifndef __RedEnemy_H__
#define __RedEnemy_H__

#include "Enemy.h"

class RedEnemy : public Enemy
{
public:
	RedEnemy(const char* pTextureFileName, const char* pTextureRollUp, const char* pTextureRollDown, const char* pTextureFlipped, float a_width, float a_height, float a_posX, float a_posY, float a_speed);
	virtual ~RedEnemy();

	virtual void Update(float a_fDeltaTime);

	void SetOscillating(bool Osc);
	void Oscillate();

private:
	float m_fTurnPoint;

};

#endif