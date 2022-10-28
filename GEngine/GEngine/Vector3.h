#pragma once
#include <cmath>
#include <limits>
namespace GEngine
{
	
	class Vector3
	{
	public:

		//Constructors

		Vector3() {}

		Vector3(float value) {
			m_x = value;
			m_y = value;
			m_z = value;
		}
		Vector3(float xValue, float yValue, float zValue) {
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

		Vector3 operator*(float scalar) {
			return { m_x * scalar, m_y * scalar, m_z * scalar };
		}

		Vector3 operator*(int scalar) {
			return { m_x * scalar, m_y * scalar,m_z * scalar };
		}

		Vector3 operator/(float scalar) {
			return { m_x / scalar, m_y / scalar, m_z / scalar };
		}

		Vector3 operator/(int scalar) {
			return { m_x / scalar, m_y / scalar, m_z / scalar };
		}
		Vector3 operator-(Vector3 substracting) {
			return { m_x - substracting.m_x, m_y - substracting.m_y, m_z - substracting.m_z };
		}
		Vector3 operator+(Vector3 additive) {
			return { m_x + additive.m_x, m_y + additive.m_y, m_z + additive.m_z };
		}
		Vector3 operator/(Vector3 dividing) {
			return { m_x / dividing.m_x, m_y / dividing.m_y, m_z / dividing.m_z };
		}
		Vector3 operator*(Vector3 scalar) {
			return { m_x * scalar.m_x, m_y * scalar.m_y, m_z * scalar.m_z };
		}
		Vector3 operator==(Vector3 compared) {
			return (fabs(m_x - compared.m_x) < FLT_EPSILON) && (fabs(m_y - compared.m_y) < FLT_EPSILON) && (fabs(m_z - compared.m_z) < FLT_EPSILON);
		}
		Vector3 operator!=(Vector3 compared) {
			return (fabs(m_x - compared.m_x) > FLT_EPSILON) || (fabs(m_y - compared.m_y) > FLT_EPSILON) || (fabs(m_z - compared.m_z) > FLT_EPSILON);
		}

		//Getters
		inline float GetMagnitude() const { return std::sqrt(m_x * m_x + m_y * m_y + m_z * m_z); }
		inline float GetSqrMagnitude() const { return std::pow(GetMagnitude(), 2); }
		inline Vector3 GetNormlized() const { return Vector3(m_x / GetMagnitude(), m_y / GetMagnitude(), m_z / GetMagnitude()); }

		//Setters
		void SetAxis(float x, float y, float z) {
			m_x = x;
			m_y = y;
			m_z = z;
		}

		//static Functions
		static Vector3 Cross(Vector3& lV, Vector3& rV) {
			return { lV.m_y * rV.m_z - lV.m_z * rV.m_y,
					 lV.m_z * rV.m_x - lV.m_x * rV.m_z,
					 lV.m_x * rV.m_y - lV.m_y * rV.m_x };
		}

		static float Dot(Vector3& lV, Vector3& rV) {
			return lV.m_x * rV.m_x + lV.m_y * rV.m_y + lV.m_z * rV.m_z;
		}

		static float Angle(Vector3& lV, Vector3& rV) {
			return acos((Dot(lV, rV)) / (lV.GetMagnitude() * rV.GetMagnitude()));
		}

		static Vector3 ClampMagnitude(Vector3& vector, float maxLength) {

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
		static Vector3 Lerp(Vector3& startingVector, Vector3& endingVector, float time) {

			if (time > 1)
				time = 1;
			if (time < 0)
				time = 0;

			return { startingVector.m_x + (endingVector.m_x - startingVector.m_x) * time,
				startingVector.m_y + (endingVector.m_y - startingVector.m_y) * time,
				startingVector.m_z + (endingVector.m_z - startingVector.m_z) * time };
		}
		static Vector3 LerpUnclamped(Vector3& startingVector, Vector3& endingVector, float time) {
			return { startingVector.m_x + (endingVector.m_x - startingVector.m_x) * time,
					startingVector.m_y + (endingVector.m_y - startingVector.m_y) * time,
					startingVector.m_z + (endingVector.m_z - startingVector.m_z) * time };
		}

		static Vector3 Reflect(Vector3& reflectedVector, Vector3& planeNormal) {
			return (reflectedVector + (planeNormal * (-2 * Dot(reflectedVector, planeNormal))));
		}
		
		static float SignedAngle(Vector3& lV, Vector3& rV,Vector3& axis) {
			float unsignedAngle = Angle(lV, rV);

			Vector3 cross = Cross(lV, rV);

			float axisCrossDot = Dot(cross, axis);
			float signAngle = (axisCrossDot >= 0 ? 1.0f : -1.0f);

			return unsignedAngle* signAngle;
		}

		static Vector3 Slerp(Vector3& startingVector, Vector3& targetVector, float time) {
			float dot = Dot(startingVector, targetVector);

			if (dot < -1.0f)
				dot = -1.0f;
			
			if (dot > 1.0f)
				dot = 1.0f;
			
			float angle = acos(dot) * time;
			Vector3 targetDirection = targetVector - startingVector * dot;
			targetDirection.GetNormlized();

			return ((startingVector * cos(angle)) + (targetDirection * sin(angle)));
		}

		static Vector3 SlerpUnclamped(Vector3& startingVector, Vector3& targetVector, float time) {
			float dot = Dot(startingVector, targetVector);

			float angle = acos(dot) * time;
			Vector3 targetDirection = targetVector - startingVector * dot;
			targetDirection.GetNormlized();

			return ((startingVector * cos(angle)) + (targetDirection * sin(angle)));

		}
		static Vector3 MoveTowards(Vector3& startingVector, Vector3& targetVector, float maxStep) {
			
			Vector3 targetDirection = (targetDirection - startingVector);

			float sqDistance = targetDirection.GetMagnitude();
			
			if (sqDistance == 0 || (maxStep >= 0 && sqDistance <= maxStep * maxStep))
				return targetDirection;

			float distance = sqrt(sqDistance);

			targetDirection = targetDirection / distance;
			targetDirection = targetDirection / maxStep;

			return { startingVector.m_x + targetDirection.m_x,
			startingVector.m_y + targetVector.m_y,
			startingVector.m_z + targetVector.m_z};
		}
		static Vector3 Normalize(Vector3& vector) {
			return vector.GetNormlized();
		}

		static Vector3 Project(Vector3& projectedV, Vector3& projectedOnV) {
			return (projectedOnV * (Dot(projectedV, projectedOnV) / Dot(projectedOnV,projectedOnV)));
		}

		static Vector3 ProjectOnPlane(Vector3& projectedV, Vector3& planeNormalV) {
			return (projectedV - Project(projectedV, planeNormalV));
		}
		static float Distance(Vector3& lV, Vector3& rV) {
			return pow(pow((lV.m_x - rV.m_x),2) + pow((lV.m_y - rV.m_y),2) + pow((lV.m_z - rV.m_z),2),0.5f);
		}

		static Vector3 Max(Vector3& lV, Vector3& rV) {
			return { (lV.m_x > rV.m_x) ? lV.m_x : rV.m_x,(lV.m_y > rV.m_y) ? lV.m_y : rV.m_y, (lV.m_z > rV.m_z) ? lV.m_z : rV.m_z };
		}
		
		static Vector3 Min(Vector3& lV, Vector3& rV) {
			return { (lV.m_x < rV.m_x) ? lV.m_x : rV.m_x,(lV.m_y < rV.m_y) ? lV.m_y : rV.m_y, (lV.m_z < rV.m_z) ? lV.m_z : rV.m_z };
		}
	public:
		float m_x{ 0.0f };
		float m_y{ 0.0f };
		float m_z{ 0.0f };

		static const Vector3 zero;
		static const Vector3 one;
		static const Vector3 up;
		static const Vector3 down;
		static const Vector3 right;
		static const Vector3 left;
		static const Vector3 forward;
		static const Vector3 back;
		static const Vector3 negativeInfinity;
		static const Vector3 positiveInfinity;
	};

	const Vector3 Vector3::zero{ 0,0,0 };
	const Vector3 Vector3::one{ 1,1,1 };
	const Vector3 Vector3::up{ 0,1,0 };
	const Vector3 Vector3::down{ 0,-1,0 };
	const Vector3 Vector3::right{ 1,0,0 };
	const Vector3 Vector3::left{ -1,0,0 };
	const Vector3 Vector3::forward{ 0,0,1 };
	const Vector3 Vector3::back{ 0,0,-1 };
	const Vector3 Vector3::negativeInfinity{std::numeric_limits<float>::min()};
	const Vector3 Vector3::positiveInfinity{std::numeric_limits<float>::max()};
}