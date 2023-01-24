#pragma once
#include "Vector3.h"
namespace GEngine 
{
	class Quaternion 
	{
	public:

		//Constructors
		Quaternion();
		
		Quaternion(const float& x, const float& y, const float& z, const float& w) {
			m_x = x;
			m_y = y;
			m_z = z;
			m_w = w;
		}

		//Operators
		Quaternion operator*(const Quaternion& rQ)
		{
			return Quaternion(
				m_w * rQ.m_x + m_x * rQ.m_w + m_y * rQ.m_z - m_z * rQ.m_y,
				m_w * rQ.m_y + m_y * rQ.m_w + m_z * rQ.m_x - m_x * rQ.m_z,
				m_w * rQ.m_z + m_z * rQ.m_w + m_x * rQ.m_y - m_y * rQ.m_x,
				m_w * rQ.m_w - m_x * rQ.m_x - m_y * rQ.m_y - m_z * rQ.m_z
			);
		}

		bool operator==(const Quaternion& rQ)
		{
			return (m_x == rQ.m_x && m_y == rQ.m_y && m_z == rQ.m_z && m_w == rQ.m_w);
		}

		bool operator!=(const Quaternion& rQ)
		{
			return (m_x != rQ.m_x || m_y != rQ.m_y || m_z != rQ.m_z || m_w != rQ.m_w);
		}

		//Public Methods.
		void Set(const float& x, const float& y, const float& z, const float& w)
		{
			m_x = x;
			m_y = y;
			m_z = z;
			m_w = w;
		}

		void Set(const Quaternion& quat)
		{
			m_x = quat.m_x;
			m_y = quat.m_y;
			m_z = quat.m_z;
			m_w = quat.m_w;
		}
		
		void SetFromRotation(const Vector3& fromDirection, const Vector3& toDirection)
		{

		}

		void SetLookRotation(const Vector3& viewDirection, const Vector3& upDirection = Vector3::up)
		{

		}

		void ToAngleAxis(float* angle, Vector3* axis)
		{

		}

		inline const Vector3 GetEularAngles(){}
		inline const Quaternion GetNormalized(){}

		char* ToString()
		{
			return nullptr;
		}

		//Static Methods

		static float Dot(const Quaternion& lQ, const Quaternion& rQ)
		{

		}

		static float Angle(const Quaternion& lQ, const Quaternion& rQ)
		{

		}

		static Quaternion AngleAxis(const float& angle, const Vector3& axis)
		{

		}

		static Quaternion Eular(const float& x, const float& y, const float& z)
		{

		}

		static Quaternion FromToRotation(const Vector3& fromDirection, const Vector3& toDirection)
		{

		}

		static Quaternion Inverse(const Quaternion& quaternion)
		{

		}

		static Quaternion Lerp(const Quaternion& lQ, const Quaternion& rQ,const float& time)
		{

		}

		static Quaternion LerpUnclamped(const Quaternion& lQ, const Quaternion& rQ, const float& time)
		{

		}

		static Quaternion LookRotation(const Vector3& forward, const Vector3 upward = Vector3::up)
		{

		}

		static Quaternion Normalize(const Quaternion& q)
		{

		}

		static Quaternion RotateTowards(const Quaternion& from, const Quaternion& to, const float& maxDegrees)
		{

		}

		static Quaternion Slerp(const Quaternion& lQ, const Quaternion rQ, const float& time)
		{

		}

		static Quaternion SlerpUnclamped(const Quaternion& lQ, const Quaternion& rQ, const float& time)
		{

		}

		float m_x{ 0.0f };
		float m_y{ 0.0f };
		float m_z{ 0.0f };
		float m_w{ 0.0f };
		static const Quaternion identity;
	};

	const Quaternion Quaternion::identity{ 0.0f,0.0f,0.0f,1.0f };
}