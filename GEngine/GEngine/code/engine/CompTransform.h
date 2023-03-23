#pragma once
#include "Component.h"
#include "Vector3.h"
#include "Quaternion.h"

enum class EGameObjectMobilityType 
{
	STATIC,
	DYNAMIC
};
class CompTransform : public Component
{
private:
	EGameObjectMobilityType m_mobilityType{ EGameObjectMobilityType::STATIC };
public:
	CompTransform() = default;
	
	GEngine::GVector3 m_position{ 0.0f,0.0f,0.0f };
	GEngine::GVector3 m_scale{ 1.0f,1.0f,1.0f };
	GEngine::GVector3 m_eularAngles{ 0.0f,0.0f,0.0f };
	GEngine::Quaternion m_rotation{ 0.0f,0.0f,0.0f,1.0f };

	void update() override {};
	void destroy() override {};
	
	EGameObjectMobilityType getGameObjectMobilityType() const { return m_mobilityType; }
};