#pragma once

#include "OgreQuaternion.h"
#include "OgreStringVector.h"
#include "OgreVector3.h"
#include <vector>
class Component;


enum class MovableObjectType
{
    NONE,
    MO_TYPE_ITEM,
    MO_TYPE_ENTITY,
    NUM_MOVABLE_OBJECT_TYPE
};

struct MovableObjectDefinition
{
    Ogre::String       m_meshName;
    Ogre::String       m_resourceGroup;
    Ogre::StringVector m_submeshMaterials;
    MovableObjectType  m_moType;
};

struct GameObjectTransform
{
    Ogre::Vector3    m_vPos;
    Ogre::Quaternion m_qRot;
    Ogre::Vector3    m_vScale;
};

struct GameObject
{
public:

    enum class GameObjectState
    {
        NONE,
        ACTIVE,
        PAUSED,
        DEAD
    };

    GameObject();
    GameObject(Ogre::uint32 id, const MovableObjectDefinition* moDefinition,
        Ogre::SceneMemoryMgrTypes type);
    virtual ~GameObject();

    Ogre::uint32 getId() const { return m_id; }
    GameObjectState getState() const { return m_state; }
    bool operator<(const GameObject* _r) const { return m_id < _r->m_id; }

    static bool OrderById(const GameObject* _l, const GameObject* _r) { return _l->m_id < _r->m_id; }

    void update(float dt);
    void addComponent(Component* pComponent);
    void removeComponent(Component* pComponent);
private:

    void updateComponents(float dt);
    Ogre::uint32 m_id;
    GameObjectState m_state;

    //----- Graphics thread members -----
    Ogre::SceneNode* m_sceneNode;
    Ogre::MovableObject* m_movableObject;

    //----- Logic and graphic threads memebers -----
    GameObjectTransform* m_transform[4];
    Ogre::SceneMemoryMgrTypes m_type;

    MovableObjectDefinition const* m_moDefinition;
    size_t m_transformBufferIdx;

    std::vector<Component*> m_components;
};

typedef std::vector<GameObject*> GameObjectsVec;