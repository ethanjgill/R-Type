#ifndef __Background_H__
#define __Background_H__

class Background
{
	public:
		Background(const char* pTextureFileName, float a_width, float a_height, float a_posX, float a_posY, bool a_vertical);
		~Background();

		void Update(float a_fDeltaTime);
		void Draw();

		void SetVelocity(float a_velocity);

		void GetPosition(float& a_x, float& a_y) const;
		void SetPosition(const float& a_x, const float& a_y);

		void SetSize(const float& a_w, const float& a_h);

		void Reset();

	private:
		float m_x;
		float m_y;

		float width;
		float height;

		float m_velocity;
		bool m_verticalMotion;

		float m_OriginalX;
		float m_OriginalY;

		int m_SpriteID;
};

#endif