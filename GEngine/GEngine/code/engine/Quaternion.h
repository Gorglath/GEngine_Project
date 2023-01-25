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

		Quaternion operator+(const Quaternion& rQ)
		{
			return { m_x + rQ.m_x, m_y + rQ.m_y, m_z + rQ.m_z, m_w + rQ.m_w };
		}
		Quaternion operator*(const float& multiplier)
		{
			return { m_x * multiplier, m_y * multiplier, m_z * multiplier, m_w * multiplier };
		}
		Quaternion operator*(const int& multiplier)
		{
			return { m_x * multiplier, m_y * multiplier, m_z * multiplier, m_w * multiplier };
		}
		Quaternion operator/(const float& divider)
		{
			return { m_x / divider, m_y / divider, m_z / divider, m_w / divider };
		}
		Quaternion operator/(const int& divider)
		{
			return { m_x / divider, m_y / divider, m_z / divider, m_w / divider };
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
		inline const Quaternion GetNormalized()
		{
			Quaternion normalized;

			float distance = sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);

			normalized.m_x = m_x / distance;
			normalized.m_y = m_y / distance;
			normalized.m_z = m_z / distance;
			normalized.m_w = m_w / distance;

			return normalized;
		}

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

		static float Angle(const Quaternion& lQ, const Quaternion& rQ)
		{
			//TODO
		}

		static Quaternion AngleAxis(const float& angle, const Vector3& axis)
		{
			Quaternion q;
			
			axis.GetNormlized();

			q.m_x = axis.m_x * sin(angle / 2);
			q.m_y = axis.m_y * sin(angle / 2);
			q.m_z = axis.m_z * sin(angle / 2);
			q.m_w = cos(angle / 2);

			return q.GetNormalized();
		}

		static Quaternion Eular(const float& x, const float& y, const float& z)
		{
			Quaternion result;

			float xRad = x * 3.14159265359 * 180;
			float yRad = y * 3.14159265359 * 180;
			float zRad = z * 3.14159265359 * 180;

			double cosy = cos(yRad / 2);
			double siny = sin(yRad / 2);
			double cosx = cos(xRad / 2);
			double sinx = sin(xRad / 2);
			double cosz = cos(zRad / 2);
			double sinz = sin(zRad / 2);
			double cosy_cosx = cosy * cosx;
			double siny_sinx = siny * sinx;
			
			result.m_w = cosy_cosx * cosz - siny_sinx * sinz;
			result.m_x = cosy_cosx * sinz + siny_sinx * cosz;
			result.m_y = siny * cosx * cosz + cosy * sinx * sinz;
			result.m_z = cosy * sinx * cosz - siny * cosx * sinz;

			return result.GetNormalized();
		}

		static Quaternion Normalize(const Quaternion& q)
		{
			Quaternion normalized;

			float distance = sqrt(q.m_w * q.m_w + q.m_x * q.m_x + q.m_y * q.m_y + q.m_z * q.m_z);

			normalized.m_x = q.m_x / distance;
			normalized.m_y = q.m_y / distance;
			normalized.m_z = q.m_z / distance;
			normalized.m_w = q.m_w / distance;

			return normalized;
		}

		static Quaternion RotateTowards(const Quaternion& from, const Quaternion& to, const float& maxDegrees)
		{
			float angle = Quaternion::Angle(from, to);
			if (angle == 0.0f)
				return to;
			return Quaternion::SlerpUnclamped(from, to, fmin(1.0f, maxDegrees / angle));
		}

		static Quaternion Lerp(const Quaternion& lQ, const Quaternion& rQ, float& time)
		{
			if (time > 1)
				time = 1;
			else if (time < 0)
				time = 0;

			return {
				lQ.m_x + (rQ.m_x - lQ.m_x) * time,
				lQ.m_y + (rQ.m_y - lQ.m_y) * time,
				lQ.m_z + (rQ.m_z - lQ.m_z) * time,
				lQ.m_w + (rQ.m_w - lQ.m_w) * time
			};
		}

		static Quaternion LerpUnclamped(const Quaternion& lQ, const Quaternion& rQ, const float& time)
		{
			return {
				lQ.m_x + (rQ.m_x - lQ.m_x) * time,
				lQ.m_y + (rQ.m_y - lQ.m_y) * time,
				lQ.m_z + (rQ.m_z - lQ.m_z) * time,
				lQ.m_w + (rQ.m_w - lQ.m_w) * time
			};
		}

		static Quaternion Slerp(const Quaternion& lQ, const Quaternion rQ, float& time)
		{
			if (time > 1)
				time = 1;
			else if (time < 0)
				time = 0;

			float halfAngle = Quaternion::Angle(lQ, rQ) / 2.0f;
			
			Quaternion Qa = lQ * sin((1 - time) * halfAngle);
			Quaternion Qb = rQ * sin(time * halfAngle);

			return ((Qa + Qb) / sin(halfAngle));
		}

		static Quaternion SlerpUnclamped(const Quaternion& lQ, const Quaternion& rQ, const float& time)
		{
			float halfAngle = Quaternion::Angle(lQ, rQ) / 2.0f;

			Quaternion Qa = lQ * sin((1 - time) * halfAngle);
			Quaternion Qb = rQ * sin(time * halfAngle);

			return ((Qa + Qb) / sin(halfAngle));
		}

		float m_x{ 0.0f };
		float m_y{ 0.0f };
		float m_z{ 0.0f };
		float m_w{ 0.0f };
		static const Quaternion identity;
	};

	const Quaternion Quaternion::identity{ 0.0f,0.0f,0.0f,1.0f };
}