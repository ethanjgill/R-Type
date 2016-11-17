#ifndef __BrownEnemy_H__
#define __BrownEnemy_H__

#include "Enemy.h"

class BrownEnemy : public Enemy
{
public:
	BrownEnemy(const char* pTexture1, const char* pTexture2, const char* pTexture3, const char* pTexture4, float a_width, float a_height, float a_posX, float a_posY, float a_speed);
	virtual ~BrownEnemy();

};

#endif