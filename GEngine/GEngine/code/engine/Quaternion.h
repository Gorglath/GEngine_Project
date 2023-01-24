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
			Quaternion targetRotation = Quaternion::FromToRotation(fromDirection, toDirection);
			
			m_x = targetRotation.m_x;
			m_y = targetRotation.m_y;
			m_z = targetRotation.m_z;
			m_w = targetRotation.m_w;
		}

		void ToAngleAxis(float* angle, Vector3* axis)
		{
			Vector3 angleAxis;
			float division = sqrt(1 - m_w * m_w);
			angleAxis.m_x = m_x / division;
			angleAxis.m_y = m_y / division;
			angleAxis.m_z = m_z / division;
			
			*angle = 2 * acos(m_w);
			*axis = angleAxis;
		}

		inline const Vector3 GetEularAngles()
		{
			Vector3 eular;

			float sinr_cosp = 2.0f * (m_w * m_x + m_y * m_z);
			float cosr_cosp = 1.0f - 2.0f * (m_x * m_x + m_y * m_y);
			eular.m_x = atan2(sinr_cosp, cosr_cosp);

			float sinp = sqrt(1.0f + 2.0f * (m_w * m_y - m_x * m_z));
			float cosp = sqrt(1.0f - 2.0f * (m_w * m_y - m_x * m_z));
			eular.m_z = 2 * atan2(sinp, cosp) - 1.570796f;

			float siny_cosp = 2.0f * (m_w * m_z + m_x * m_y);
			float cosy_cosp = 1.0f - 2.0f * (m_y * m_y + m_z * m_z);
			eular.m_y = atan2(siny_cosp, cosy_cosp);

			return eular;
		}
		inline const Quaternion GetNormalized(){}

		char* ToString()
		{
			char quatString[7];
			quatString[0] = m_x;
			quatString[1] = '-';
			quatString[2] = m_y;
			quatString[3] = '-';
			quatString[4] = m_z;
			quatString[5] = '-';
			quatString[6] = m_w;
			return quatString;
		}

		//Static Methods

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
			Quaternion result;
			Vector3 cross = Vector3::Cross(fromDirection, toDirection);
			result.m_x = cross.m_x;
			result.m_y = cross.m_y;
			result.m_z = cross.m_z;
			result.m_w = sqrt(fromDirection.GetSqrMagnitude() * toDirection.GetSqrMagnitude()) + Vector3::Dot(fromDirection, toDirection);
			
			return result.GetNormalized();
		}

		static Quaternion Lerp(const Quaternion& lQ, const Quaternion& rQ,const float& time)
		{

		}

		static Quaternion LerpUnclamped(const Quaternion& lQ, const Quaternion& rQ, const float& time)
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