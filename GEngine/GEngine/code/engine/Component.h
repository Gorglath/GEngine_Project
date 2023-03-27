#pragma once

namespace GEngine
{
class GameEntity;
class Component
{
public:
	virtual ~Component() {};

	bool m_isActive{ true };
	GEngine::GameEntity* m_gameEntity{ nullptr };

	virtual void update() = 0;
	virtual void destroy() = 0;
};
}