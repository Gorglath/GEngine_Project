#pragma once
#include "CompCollider.h"
namespace GEngine 
{
	class CompBoxCollider : public CompCollider
	{
	private:
		float m_xWidth{ 1.0f };
		float m_yHeight{ 1.0f };
		float m_zWidth{ 1.0f };
	public:
		CompBoxCollider(float xWidth, float yHeight, float zWidth) :
			m_xWidth{ xWidth }, m_yHeight{ yHeight }, m_zWidth{ zWidth }
		{
		}
		void setScale(float xWidth, float yHeight, float zWidth)
		{
			m_xWidth = xWidth;
			m_yHeight = yHeight;
			m_zWidth = zWidth;
		}
		float getXWidth() const { return m_xWidth; }
		float getYHeight() const { return m_yHeight; }
		float getZWidth() const { return m_zWidth; }
	};
}