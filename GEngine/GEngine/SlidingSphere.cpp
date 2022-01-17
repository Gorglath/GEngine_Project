#include "SlidingSphere.h"

void SlidingSphere::createSphere(SceneManager* sceneManager)
{
    m_sphereMesh = sceneManager->createItem(
        "Sphere1000.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
        Ogre::SCENE_DYNAMIC);
    
    m_sphereNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
        ->createChildSceneNode(Ogre::SCENE_DYNAMIC);

    m_sphereNode->attachObject(m_sphereMesh);
    m_sphereNode->setPosition(0.0f, 5.0f, 0.0f);
}

void SlidingSphere::update(float dt)
{
    if (m_shouldApplyGravity)
    {
        m_sphereNode->translate(Vector3::NEGATIVE_UNIT_Y * dt);
    }
}
