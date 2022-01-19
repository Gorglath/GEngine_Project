#include "SlidingSphere.h"
#include <math.h>
void SlidingSphere::createSphere(SceneManager* sceneManager)
{
    m_sphereMesh = sceneManager->createItem(
        "Sphere1000.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
        Ogre::SCENE_DYNAMIC);
    
    m_sphereNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
        ->createChildSceneNode(Ogre::SCENE_DYNAMIC);

    m_sphereNode->attachObject(m_sphereMesh);
    m_sphereYPosition = m_sphereNode->getScale().y / 2.0f;
    m_sphereNode->setPosition(0.0f, m_sphereYPosition, 0.0f);
}

void SlidingSphere::update(float dt,InputData inputData)
{
    Vector2 playerInput = Vector2::ZERO;
    if (inputData.m_isWKeyPressed)
    {
        playerInput.y += 1;
    }
    if (inputData.m_isAKeyPressed)
    {
        playerInput.x += 1;
    }
    if (inputData.m_isSKeyPressed)
    {
        playerInput.y -= 1;
    }
    if (inputData.m_isDKeyPressed)
    {
        playerInput.x -= 1;
    }
    
    if (!playerInput.isZeroLength()) 
    {
        //Clamp the input magnitude.
        float minValue = fminf(playerInput.length(), 1.0f) / playerInput.length();
        playerInput = Vector2(minValue * playerInput.x, minValue * playerInput.y);

        Vector3 currentPos = m_sphereNode->getPosition();
        currentPos.z += playerInput.y * dt;
        currentPos.x += playerInput.x * dt;
        m_sphereNode->setPosition(currentPos);
    }
}
