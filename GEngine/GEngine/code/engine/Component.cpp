#include "Component.h"
#include "GameObject.h"

Component::Component(GameObject* pOwner, int updateOrder) : m_owner{*pOwner},m_updateOrder{updateOrder}
{
}

Component::~Component()
{
}

void Component::update(float dt)
{
}
