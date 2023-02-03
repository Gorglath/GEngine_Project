#include "SlidingSphere.h"
#include <math.h>
#include <iostream>
void SlidingSphere::createSphere(SceneManager* sceneManager)
{
   m_entityNode = m_meshLoader.loadMesh("Sphere1000.mesh", sceneManager);
   m_meshLoader.m_gameEntity = this;
}

void SlidingSphere::update(float dt,InputData inputData)
{
    GVector3 playerInput = GVector3::zeroVector;
    if (inputData.m_isWKeyPressed)
    {
        playerInput.m_y += 1;
    }
    if (inputData.m_isAKeyPressed)
    {
        playerInput.m_x += 1;
    }
    if (inputData.m_isSKeyPressed)
    {
        playerInput.m_y -= 1;
    }
    if (inputData.m_isDKeyPressed)
    {
        playerInput.m_x -= 1;
    }
    
    if (!playerInput.IsZero())
    {
        //Clamp the input magnitude.
        float minValue = fminf(playerInput.Length(), 1.0f) / playerInput.Length();
        playerInput = GVector3(minValue * playerInput.m_x,0.0f, minValue * playerInput.m_y);
    }
     
    GVector3 desiredVelocity = GVector3(playerInput.m_x, 0.0f, playerInput.m_z) * m_movementSpeed;
        
    clampAcceleration(desiredVelocity, dt);
        
        
    GVector3 translation = m_velocity * dt;
    GVector3 newPosition = m_transform.m_position;
  
    newPosition += translation;

    clampNewPositionToBounds(newPosition);
    
    m_transform.m_position = newPosition;
    
    m_entityNode->setPosition(m_transform.m_position);
}

void SlidingSphere::clampNewPositionToBounds(GEngine::GVector3& newPos)
{
    if (m_allowedArea.top < newPos.m_z)
    {
        newPos.m_z = m_allowedArea.top;
        m_velocity.m_z = -m_velocity.m_z * m_bounceiness;
    }
    else if (m_allowedArea.bottom > newPos.m_z)
    {
        newPos.m_z = m_allowedArea.bottom;
        m_velocity.m_z = -m_velocity.m_z * m_bounceiness;
    }

    if (m_allowedArea.right < newPos.m_x)
    {
        newPos.m_x = m_allowedArea.right;
        m_velocity.m_x = -m_velocity.m_x * m_bounceiness;
    }
    else if (m_allowedArea.left > newPos.m_x)
    {
        newPos.m_x = m_allowedArea.left;
        m_velocity.m_x = -m_velocity.m_x * m_bounceiness;
    }
}

void SlidingSphere::clampAcceleration(GEngine::GVector3& desiredVelocity,float dt)
{
    float maxSpeedChange = m_accelerationSpeed * dt;

    m_velocity.m_x = (abs(desiredVelocity.m_x - m_velocity.m_x) <= maxSpeedChange) ?
        desiredVelocity.m_x :
        m_velocity.m_x + ((desiredVelocity.m_x - m_velocity.m_x >= 0) ? 1.0f : -1.0f) * maxSpeedChange;
    m_velocity.m_z = (abs(desiredVelocity.m_z - m_velocity.m_z) <= maxSpeedChange) ?
        desiredVelocity.m_z :
        m_velocity.m_z + ((desiredVelocity.m_z - m_velocity.m_z >= 0) ? 1.0f : -1.0f) * maxSpeedChange;
}
