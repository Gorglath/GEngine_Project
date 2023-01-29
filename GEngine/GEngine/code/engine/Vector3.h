#pragma once

#include <cmath>
#include <limits>
#include "OgreVector3.h"
namespace GEngine
{
	class GVector3
	{
	public:

		//Constructors

		GVector3() {}

		GVector3(const float& value) {
			m_x = value;
			m_y = value;
			m_z = value;
		}
		GVector3(const float& xValue, const float& yValue, const float& zValue) {
			m_x = xValue;
			m_y = yValue;
			m_z = zValue;
		}
		GVector3(GVector3* nVector) {
			m_x = nVector->m_x;
			m_y = nVector->m_y;
			m_z = nVector->m_z;
		}

		//Destructor
		~GVector3() {}

		//Operators
		void operator=(const GVector3& scalar) {
			m_x = scalar.m_x;
			m_y = scalar.m_y;
			m_z = scalar.m_z;
		}
		void operator*=(const GVector3& scalar) {
			m_x *= scalar.m_x;
			m_y *= scalar.m_y;
			m_z *= scalar.m_z;
		}
		void operator/=(const GVector3& dividing) {
			m_x /= dividing.m_x;
			m_y /= dividing.m_y;
			m_z /= dividing.m_z;
		}
		void operator-=(const GVector3& substracting) {
			m_x -= substracting.m_x;
			m_y -= substracting.m_y;
			m_z -= substracting.m_z;
		}
		void operator+=(const GVector3& additive) {
			m_x += additive.m_x;
			m_y += additive.m_y;
			m_z += additive.m_z;
		}
		operator Ogre::Vector3() const {
			return { m_x,m_y,m_z };
		}
		GVector3 operator*(const float& scalar) {
			return { m_x * scalar, m_y * scalar, m_z * scalar };
		}

		GVector3 operator*(const int& scalar) {
			return { m_x * scalar, m_y * scalar,m_z * scalar };
		}

		GVector3 operator/(const float& scalar) {
			return { m_x / scalar, m_y / scalar, m_z / scalar };
		}

		GVector3 operator/(const int& scalar) {
			return { m_x / scalar, m_y / scalar, m_z / scalar };
		}
		GVector3 operator-(const GVector3& substracting) {
			return { m_x - substracting.m_x, m_y - substracting.m_y, m_z - substracting.m_z };
		}
		GVector3 operator+(const GVector3& additive) {
			return { m_x + additive.m_x, m_y + additive.m_y, m_z + additive.m_z };
		}
		GVector3 operator/(const GVector3& dividing) {
			return { m_x / dividing.m_x, m_y / dividing.m_y, m_z / dividing.m_z };
		}
		
		GVector3 operator*(const GVector3& scalar) {
			return { m_x * scalar.m_x, m_y * scalar.m_y, m_z * scalar.m_z };
		}
		
		GVector3 operator==(const GVector3& compared) {
			return (fabs(m_x - compared.m_x) < FLT_EPSILON) && (fabs(m_y - compared.m_y) < FLT_EPSILON) && (fabs(m_z - compared.m_z) < FLT_EPSILON);
		}
		GVector3 operator!=(const GVector3& compared) {
			return (fabs(m_x - compared.m_x) > FLT_EPSILON) || (fabs(m_y - compared.m_y) > FLT_EPSILON) || (fabs(m_z - compared.m_z) > FLT_EPSILON);
		}
		//Public Fuctions

		bool IsZero() {
			return (m_x == 0.0f && m_y == 0.0f && m_z == 0.0f);
		}

		float Length() {
			return (sqrtf(m_x * m_x + m_y * m_y + m_z * m_z));
		}
		//Getters
		inline float GetMagnitude() const { return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z); }
		inline float GetSqrMagnitude() const { return std::pow(GetMagnitude(), 2); }
		inline GVector3 GetNormlized() const { return GVector3(m_x / GetMagnitude(), m_y / GetMagnitude(), m_z / GetMagnitude()); }

		//Setters
		void SetAxis(const float& x, const float& y, const float& z) {
			m_x = x;
			m_y = y;
			m_z = z;
		}

		//static Functions
		static GVector3 Cross(const GVector3& lV, const GVector3& rV) {
			return { lV.m_y * rV.m_z - lV.m_z * rV.m_y,
					 lV.m_z * rV.m_x - lV.m_x * rV.m_z,
					 lV.m_x * rV.m_y - lV.m_y * rV.m_x };
		}

		static float Dot(const GVector3& lV, const GVector3& rV) {
			return lV.m_x * rV.m_x + lV.m_y * rV.m_y + lV.m_z * rV.m_z;
		}

		static float Angle(const GVector3& lV, const GVector3& rV) {
			return acos((Dot(lV, rV)) / (lV.GetMagnitude() * rV.GetMagnitude()));
		}

		static GVector3 ClampMagnitude(const GVector3& vector, const float& maxLength) {

			float vectorSqrMag = vector.GetSqrMagnitude();
			if (vectorSqrMag > maxLength * maxLength)
			{
				float newMag = sqrt(vectorSqrMag);

				float normalX = vector.m_x / newMag;
				float normalY = vector.m_y / newMag;
				float normalZ = vector.m_z / newMag;

				return { normalX * maxLength, normalY * maxLength, normalZ * maxLength };
			}

			return vector;
		}
		static GVector3 Lerp(const GVector3& startingVector, const GVector3& endingVector, float& time) {

			if (time > 1)
				time = 1;
			if (time < 0)
				time = 0;

			return { startingVector.m_x + (endingVector.m_x - startingVector.m_x) * time,
				startingVector.m_y + (endingVector.m_y - startingVector.m_y) * time,
				startingVector.m_z + (endingVector.m_z - startingVector.m_z) * time };
		}

		static GVector3 LerpUnclamped(const GVector3& startingVector, const GVector3& endingVector, float& time) {
			return { startingVector.m_x + (endingVector.m_x - startingVector.m_x) * time,
					startingVector.m_y + (endingVector.m_y - startingVector.m_y) * time,
					startingVector.m_z + (endingVector.m_z - startingVector.m_z) * time };
		}

		static GVector3 Reflect(GVector3& reflectedVector, GVector3& planeNormal) {
			return (reflectedVector + (planeNormal * (-2 * Dot(reflectedVector, planeNormal))));
		}
		
		static float SignedAngle(const GVector3& lV, const GVector3& rV, const GVector3& axis) {
			float unsignedAngle = Angle(lV, rV);

			GVector3 cross = Cross(lV, rV);

			float axisCrossDot = Dot(cross, axis);
			float signAngle = (axisCrossDot >= 0 ? 1.0f : -1.0f);

			return unsignedAngle* signAngle;
		}

		static GVector3 Slerp(GVector3& startingVector, GVector3& targetVector, const float& time) {
			float dot = Dot(startingVector, targetVector);

			if (dot < -1.0f)
				dot = -1.0f;
			
			if (dot > 1.0f)
				dot = 1.0f;
			
			float angle = acos(dot) * time;
			GVector3 targetDirection = targetVector - startingVector * dot;
			targetDirection.GetNormlized();

			return ((startingVector * cos(angle)) + (targetDirection * sin(angle)));
		}

		static GVector3 SlerpUnclamped(GVector3& startingVector, GVector3& targetVector, const float& time) {
			float dot = Dot(startingVector, targetVector);

			float angle = acos(dot) * time;
			GVector3 targetDirection = targetVector - startingVector * dot;
			targetDirection.GetNormlized();

			return ((startingVector * cos(angle)) + (targetDirection * sin(angle)));

		}
		static GVector3 MoveTowards(GVector3& startingVector, GVector3& targetVector,const float& maxStep) {
			
			GVector3 targetDirection = (targetVector - startingVector);

			float sqDistance = targetDirection.GetMagnitude();
			
			if (sqDistance == 0 || (maxStep >= 0 && sqDistance <= maxStep * maxStep))
				return targetDirection;

			float distance = sqrt(sqDistance);

			targetDirection = targetDirection / distance;
			targetDirection = targetDirection * maxStep;

			return { startingVector.m_x + targetDirection.m_x,
			startingVector.m_y + targetDirection.m_y,
			startingVector.m_z + targetDirection.m_z};
		}
		static GVector3 Normalize(const GVector3& vector) {
			return vector.GetNormlized();
		}

		static GVector3 Project(GVector3& projectedV,GVector3& projectedOnV) {
			return (projectedOnV * (Dot(projectedV, projectedOnV) / Dot(projectedOnV,projectedOnV)));
		}

		static GVector3 ProjectOnPlane(GVector3& projectedV, GVector3& planeNormalV) {
			return (projectedV - Project(projectedV, planeNormalV));
		}
		static float Distance(GVector3& lV, GVector3& rV) {
			return sqrt(pow((lV.m_x - rV.m_x),2) + pow((lV.m_y - rV.m_y),2) + pow((lV.m_z - rV.m_z),2));
		}

		static GVector3 Max(GVector3& lV, GVector3& rV) {
			return { (lV.m_x > rV.m_x) ? lV.m_x : rV.m_x,(lV.m_y > rV.m_y) ? lV.m_y : rV.m_y, (lV.m_z > rV.m_z) ? lV.m_z : rV.m_z };
		}
		
		static GVector3 Min(GVector3& lV, GVector3& rV) {
			return { (lV.m_x < rV.m_x) ? lV.m_x : rV.m_x,(lV.m_y < rV.m_y) ? lV.m_y : rV.m_y, (lV.m_z < rV.m_z) ? lV.m_z : rV.m_z };
		}
	public:
		float m_x{ 0.0f };
		float m_y{ 0.0f };
		float m_z{ 0.0f };

		static const GVector3 zeroVector;
		static const GVector3 oneVector;
		static const GVector3 upVector;
		static const GVector3 downVector;
		static const GVector3 rightVector;
		static const GVector3 leftVector;
		static const GVector3 forwardVector;
		static const GVector3 backVector;
		static const GVector3 negativeInfinityVector;
		static const GVector3 positiveInfinityVector;
	};
}