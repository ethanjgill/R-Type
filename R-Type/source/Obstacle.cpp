#include "Obstacle.h"
#include "Application.h"


Obstacle::Obstacle(const char* pTexture0, const char* pTexture1, const char* pTexture2, const char* pTexture3, float a_width, float a_height, float a_posX, float a_posY, float a_speed) : Entity(pTexture0, pTexture1, pTexture2, pTexture3, a_width, a_height, a_posX, a_posY, a_speed)
{
}

Obstacle::~Obstacle()
{
}