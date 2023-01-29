#pragma once
#include "GameEntity.h"
#include "CompBoxCollider.h"
#include "CompSphereCollider.h"
#include "Boundary.h"
#include "OgreVector3.h"

class CollisionUtils
{
public:
	static bool isColliding(CompCollider* lCollider, CompCollider* rCollider)
	{
		bool leftSphere = false;
		bool rightSphere = false;

		if (dynamic_cast<CompBoxCollider*>(lCollider) == nullptr)
			leftSphere = true;
		if (dynamic_cast<CompSphereCollider*>(rCollider) == nullptr)
			rightSphere = true;

		bool isCollision = false;

		if (leftSphere && rightSphere)
			isCollision = isSphereSphereOverlap(dynamic_cast<CompSphereCollider*>(lCollider), dynamic_cast<CompSphereCollider*>(rCollider));
		else if (leftSphere)
			isCollision = isBoxSphereOverlap(dynamic_cast<CompBoxCollider*>(rCollider), dynamic_cast<CompSphereCollider*>(lCollider));
		else if (rightSphere)
			isCollision = isBoxSphereOverlap(dynamic_cast<CompBoxCollider*>(lCollider), dynamic_cast<CompSphereCollider*>(rCollider));
		else
			isCollision = isBoxBoxOverlap(dynamic_cast<CompBoxCollider*>(lCollider), dynamic_cast<CompBoxCollider*>(rCollider));

		return isCollision;
	}

	static bool isBoxSphereOverlap(CompBoxCollider* boxCollider, CompSphereCollider* sphereCollider)
	{
		BoxBoundary boxBoundary = calculateBoxBoundary(boxCollider);
		GEngine::GVector3 sphereCenter = sphereCollider->m_gameEntity->m_transform.m_position;
		float closestX = getMax(boxBoundary.m_left, getMin(sphereCenter.m_x, boxBoundary.m_right));
		float closestY = getMax(boxBoundary.m_bot, getMin(sphereCenter.m_y, boxBoundary.m_top));
		float closestZ = getMax(boxBoundary.m_back, getMin(sphereCenter.m_z, boxBoundary.m_front));

		float distance = Math::Sqrt((closestX - sphereCenter.m_x) * (closestX - sphereCenter.m_x) +
			(closestY - sphereCenter.m_y) * (closestY - sphereCenter.m_y) +
			(closestZ - sphereCenter.m_z) * (closestZ - sphereCenter.m_z));

		return distance < sphereCollider->getRadius();
	}

	static bool isBoxBoxOverlap(CompBoxCollider* lBoxCollider, CompBoxCollider* rBoxCollider)
	{
		BoxBoundary lBoxBoundary = calculateBoxBoundary(lBoxCollider);
		BoxBoundary rBoxBoundary = calculateBoxBoundary(rBoxCollider);

		if (lBoxBoundary.m_right <= rBoxBoundary.m_left)
			return false;
		else if (lBoxBoundary.m_left >= rBoxBoundary.m_right)
			return false;
		else if (lBoxBoundary.m_front <= rBoxBoundary.m_back)
			return false;
		else if (lBoxBoundary.m_back >= rBoxBoundary.m_front)
			return false;
		else if (lBoxBoundary.m_top <= rBoxBoundary.m_bot)
			return false;
		else if (lBoxBoundary.m_bot >= rBoxBoundary.m_top)
			return false;

		return true;
	}

	static bool isSphereSphereOverlap(CompSphereCollider* lSphereCollider, CompSphereCollider* rSphereCollider)
	{
		GEngine::GVector3 lSphereCenter = lSphereCollider->m_gameEntity->m_transform.m_position;
		GEngine::GVector3 rSphereCenter = rSphereCollider->m_gameEntity->m_transform.m_position;

		float distance = Math::Sqrt((lSphereCenter.m_x - rSphereCenter.m_x) * (lSphereCenter.m_x - rSphereCenter.m_x) +
			(lSphereCenter.m_y - rSphereCenter.m_y) * (lSphereCenter.m_y - rSphereCenter.m_y) +
			(lSphereCenter.m_z - rSphereCenter.m_z) * (lSphereCenter.m_z - rSphereCenter.m_z));

		return distance < (lSphereCollider->getRadius() + rSphereCollider->getRadius());
	}

	static float getMax(float lValue, float rValue)
	{
		return ((lValue > rValue) ? lValue : rValue);
	}
	static float getMin(float lValue, float rValue)
	{
		return ((lValue < rValue) ? lValue : rValue);
	}
	static BoxBoundary calculateBoxBoundary(CompBoxCollider* boxCollider)
	{
		GEngine::GVector3 boxCenter = boxCollider->m_gameEntity->m_transform.m_position;
		BoxBoundary boxBoundary;

		boxBoundary.m_right = boxCenter.m_x + boxCollider->getXWidth();
		boxBoundary.m_left = boxCenter.m_x - boxCollider->getXWidth();
		boxBoundary.m_front = boxCenter.m_z + boxCollider->getZWidth();
		boxBoundary.m_back = boxCenter.m_z - boxCollider->getZWidth();
		boxBoundary.m_top = boxCenter.m_y + boxCollider->getYHeight();
		boxBoundary.m_bot = boxCenter.m_y - boxCollider->getYHeight();

		return boxBoundary;
	}
};