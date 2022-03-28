#pragma once
#include "Ogre.h"
#include "CompTransform.h"
#include "CompCollider.h"
#include <vector>
using namespace Ogre;
class GameEntity
{
public:
	GameEntity();

	Ogre::String m_name{ "" };
	Ogre::uint16 m_id{0};
	bool m_active{ true };
	CompTransform m_transform;

	virtual void load();

	virtual void start();
	virtual void onStart();

	virtual void update(float dt);
	virtual void onUpdate(float dt);

	void addComponent(Component* component)
	{
		if (!hasComponent(component))
		{
			component->m_gameEntity = this;
			m_components.push_back(component);
		}
	}

	template<typename T>
	void removeComponent()
	{
		if (hasComponent<T>())
		{
			for (int i = 0; i < m_components.size(); i++)
			{
				if (T* subComponent = dynamic_cast<T*>(m_components[i]))
				{
					m_components[i].destroy();
					m_components.erase(m_components.begin() + i);
					break;
				}
			}
		}
	}

	template<typename T>
	T* getComponent()
	{
		for (auto component : m_components)
		{
			if (T* subComponent = dynamic_cast<T*>(component))
			{
				return subComponent;
			}
		}

		return nullptr;
	}

	template<typename T>
	bool hasComponent()
	{
		for (auto component : m_components)
		{
			if (T* subComponent = dynamic_cast<T*>(component))
			{
				return true;
			}
		}
		return false;
	}

	bool hasComponent(Component* component)
	{
		if (std::find(m_components.begin(), m_components.end(), component) != m_components.end())
			return true;
		return false;
	}

	virtual void onColliderEnter(CompCollider* collider);
	virtual void destroy();

private:
	std::vector<Component*> m_components;
	bool m_isInitialized = false;
};

