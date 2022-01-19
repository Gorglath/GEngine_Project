#include "SlidingSphere.h"

void SlidingSphere::createSphere(SceneManager* sceneManager)
{
    m_sphereMesh = sceneManager->createItem(
        "Sphere1000.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
        Ogre::SCENE_DYNAMIC);
    
    m_sphereNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
        ->createChildSceneNode(Ogre::SCENE_DYNAMIC);

    m_sphereNode->attachObject(m_sphereMesh);
    m_sphereNode->setPosition(0.0f, m_sphereNode->getScale().y/2.0f, 0.0f);
}

void SlidingSphere::update(float dt,InputData inputData)
{
    Ogre::Log log("Input.txt");
    String s = "Input : ";
    if (inputData.m_isWKeyPressed)
    {
        s += "W ";
    }
    if (inputData.m_isAKeyPressed)
    {
        s += "A ";
    }
    if (inputData.m_isSKeyPressed)
    {
        s += "S ";
    }
    if (inputData.m_isDKeyPressed)
    {
        s += "D ";
    }
    log.logMessage(s);

}
