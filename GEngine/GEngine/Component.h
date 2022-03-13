#pragma once
class GameObject;

class Component
{
public:
	Component(GameObject* pOwner, int updateOrder = 100);
	Component() = delete;
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int getUpdateOrder() const { return m_updateOrder; }

	virtual void update(float dt);
protected:
	GameObject& m_owner;
	int m_updateOrder;
};

