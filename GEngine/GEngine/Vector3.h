#pragma once
#include <Ogre.h>

namespace GEngine
{
	class Vector3
	{
	public:

		//Constructors

		Vector3() {}

		Vector3(float& value) {
			m_x = value;
			m_y = value;
			m_z = value;
		}
		Vector3(float xValue, float yValue, float zValue){
			m_x = xValue;
			m_y = yValue;
			m_z = zValue;
		}
		Vector3(Vector3* nVector) {
			m_x = nVector->m_x;
			m_y = nVector->m_y;
			m_z = nVector->m_z;
		}
		
		//Destructor
		~Vector3() {}

		//Operators
		Vector3 operator-(Vector3& substracting) {
			return Vector3(m_x - substracting.m_x, m_y - substracting.m_y, m_z - substracting.m_z);
		}
		Vector3 operator+(Vector3& additive) {
			return Vector3(m_x + additive.m_x, m_y + additive.m_y, m_z + additive.m_z);
		}
		Vector3 operator/(Vector3& dividing) {
			return Vector3(m_x / dividing.m_x, m_y / dividing.m_y, m_z / dividing.m_z);
		}
		Vector3 operator*(Vector3& scalar) {
			return Vector3(m_x * scalar.m_x, m_y * scalar.m_y, m_z * scalar.m_z);
		}

		inline float GetMagnitude() const { return Ogre::Math::Sqrt(m_x*m_x + m_y*m_y + m_z*m_z); }
		inline float GetSqrMagnitude() const { return Ogre::Math::Sqr(GetMagnitude()); }
		inline Vector3 GetNormlized() const { return Vector3(m_x / GetMagnitude(), m_y / GetMagnitude(), m_z / GetMagnitude()); }

	public:
		float m_x{ 0.0f };
		float m_y{ 0.0f };
		float m_z{ 0.0f };
	};
}