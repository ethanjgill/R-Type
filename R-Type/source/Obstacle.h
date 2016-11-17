#ifndef __Obstacle_H__
#define __Obstacle_H__

#include "Entity.h"

class Obstacle : public Entity
{
public:
	Obstacle(const char* pTexture0, const char* pTexture1, const char* pTexture2, const char* pTexture3, float a_width, float a_height, float a_posX, float a_posY, float a_speed);
	virtual ~Obstacle();
};

#endif