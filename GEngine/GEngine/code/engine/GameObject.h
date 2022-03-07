#pragma once

#include "OgreQuaternion.h"
#include "OgreStringVector.h"
#include "OgreVector3.h"

enum MovableObjectType
{
    MoTypeItem,
    MoTypeEntity,
    NumMovableObjectType
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
private:
    Ogre::uint32 m_id;

public:

    //----- Graphics thread members -----
    Ogre::SceneNode* m_sceneNode;
    Ogre::MovableObject* m_movableObject;

    //----- Logic and graphic threads memebers -----
    GameObjectTransform* m_transform[4];
    Ogre::SceneMemoryMgrTypes m_type;

    MovableObjectDefinition const* m_moDefinition;
    size_t m_transformBufferIdx;

    GameObject(Ogre::uint32 id, const MovableObjectDefinition* moDefinition,
        Ogre::SceneMemoryMgrTypes type) :
        m_id(id),
        m_sceneNode(0),
        m_movableObject(0),
        m_type(type),
        m_moDefinition(moDefinition),
        m_transformBufferIdx(0)
    {
        for (int i = 0; i < 4; ++i)
            m_transform[i] = 0;
    }

    Ogre::uint32 getId() const { return m_id; }

    bool operator<(const GameObject* _r) const { return m_id < _r->m_id; }

    static bool OrderById(const GameObject* _l, const GameObject* _r) { return _l->m_id < _r->m_id; }
};

typedef std::vector<GameObject*> GameObjectsVec;