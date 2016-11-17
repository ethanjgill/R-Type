#ifndef __Entity_H__
#define __Entity_H__

class Entity
{
public:
	Entity(const char* pTexture1, const char* pTexture2, const char* pTexture3, const char* pTexture4, float a_width, float a_height, float a_posX, float a_posY, float a_speed, float a_width1 = 0.f, float a_width2 = 0.f, float a_width3 = 0.f, float a_height1 = 0.f, float a_height2 = 0.f, float a_height3 = 0.f);
	virtual ~Entity();

	virtual void Update(float a_fDeltaTime);
	virtual void Draw();

	void SetVelocity(float a_XVelocity, float a_YVelocity);
	void GetVelocity(float& a_XVelocity, float& a_YVelocity) const;

	void GetPosition(float& a_x, float& a_y) const;
	void SetPosition(const float& a_x, const float& a_y);

	void GetSize(float& a_w, float& a_h) const;
	void SetSize(const float& a_w, const float& a_h);

	void GetEdges(float(&a_x)[2], float(&a_y)[2]) const;
	void SetEdges(const float& a_w, const float& a_h);

	virtual void Reset();

protected:
	float m_x;
	float m_y;

	float m_OriginalX;
	float m_OriginalY;

	float width;
	float height;

	float m_velocity[2];

	float m_boundaryX[2];
	float m_boundaryY[2];

	int m_currentSprite;

	int m_SpriteID[4];
};

#endif