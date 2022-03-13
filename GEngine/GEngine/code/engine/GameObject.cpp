#include "GameObject.h"
#include <algorithm>
#include "Component.h"

GameObject::GameObject()
{
    m_state = GameObjectState::ACTIVE;
}

GameObject::GameObject(Ogre::uint32 id, const MovableObjectDefinition* moDefinition, Ogre::SceneMemoryMgrTypes type) :
    m_id(id),
    m_sceneNode(0),
    m_movableObject(0),
    m_type(type),
    m_moDefinition(moDefinition),
    m_transformBufferIdx(0)
{
    for (int i = 0; i < 4; ++i)
        m_transform[i] = 0;

    m_state = GameObjectState::ACTIVE;
}

void GameObject::update(float dt)
{
    if (m_state == GameObject::GameObjectState::ACTIVE)
    {
        updateComponents(dt);
    }
}

void GameObject::addComponent(Component* pComponent)
{
    int order = pComponent->getUpdateOrder();
    auto iter = std::begin(m_components);
    for (; iter != std::end(m_components); ++iter)
    {
        if (order < (*iter)->getUpdateOrder())
        {
            break;
        }
    }

    m_components.insert(iter, pComponent);
}

void GameObject::removeComponent(Component* pComponent)
{
    auto iter = std::find(std::begin(m_components), std::end(m_components), m_components);
    if (iter != std::end(m_components))
    {
        m_components.erase(iter);
    }
}

void GameObject::updateComponents(float dt)
{
}
