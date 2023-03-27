#pragma once
#include "CompCollider.h"
namespace GEngine
{
	class CompSphereCollider : public CompCollider
	{
	public:
		CompSphereCollider(float radius) :m_radius{ radius } {}

		void setRadius(float radius) { m_radius = radius; }
		float getRadius() const { return m_radius; }
	private:
		float m_radius{ 1.0f };
	};
}