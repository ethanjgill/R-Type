#ifndef __Blast_H__
#define __Blast_H__

#include "Entity.h"

class Blast : public Entity
{
public:
	Blast(const char* pTextureFileName, const char* pTextureMed, const char* pTextureMed2, const char* pTextureCharged, float a_width, float a_height, float a_x, float a_y);
	virtual ~Blast();

	virtual void Update(float a_fDeltaTime);

	void SetBoundary(const float& a_x, const float& a_y);

	void SetSprite(int spriteID);
	int GetSprite();

	void Reset();

private:

	float m_fXBoundary;
	float m_fYBoundary;

};

#endif