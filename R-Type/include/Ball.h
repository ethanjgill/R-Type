#ifndef __BALL_H__
#define __BALL_H__

class Ball
{
public:
	Ball(const char* pTextureFileName, float a_width, float a_height);
	~Ball();

	void Update(float a_fDeltaTime);
	void Draw();
	void Reset();

	void GetPosition(float& a_x, float& a_y) const;
	void SetPosition(const float& a_x, const float& a_y);

	void SetVelocity(int a_x, int a_y);
	void SetBoundary(const float& a_x, const float& a_y);

private:
	float m_x;
	float m_y;
	int m_velocityX;
	int m_velocityY;

	float m_fSize;

	float m_fXBoundary;
	float m_fYBoundary;

	int m_SpriteID;
};

#endif