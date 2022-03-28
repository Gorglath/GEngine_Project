#include "SlidingSphere.h"
#include <math.h>
void SlidingSphere::createSphere(SceneManager* sceneManager)
{
   m_sphereNode = m_meshLoader.loadMesh("Sphere1000.mesh", sceneManager);
   m_meshLoader.m_gameEntity = this;
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
    }
        Vector3 desiredVelocity = Vector3(playerInput.x, 0.0f, playerInput.y) * m_movementSpeed;
        
        clampAcceleration(desiredVelocity, dt);
        
        Vector3 translation = m_velocity * dt;
        Vector3 newPosition = m_transform.m_position;
        newPosition += translation;

        clampNewPositionToBounds(newPosition);
        
        m_transform.m_position = newPosition;
        m_sphereNode->setPosition(m_transform.m_position);
}

void SlidingSphere::clampNewPositionToBounds(Vector3& newPos)
{
    if (m_allowedArea.top < newPos.z)
    {
        newPos.z = m_allowedArea.top;
        m_velocity.z = -m_velocity.z * m_bounceiness;
    }
    else if (m_allowedArea.bottom > newPos.z)
    {
        newPos.z = m_allowedArea.bottom;
        m_velocity.z = -m_velocity.z * m_bounceiness;
    }

    if (m_allowedArea.right < newPos.x)
    {
        newPos.x = m_allowedArea.right;
        m_velocity.x = -m_velocity.x * m_bounceiness;
    }
    else if (m_allowedArea.left > newPos.x)
    {
        newPos.x = m_allowedArea.left;
        m_velocity.x = -m_velocity.x * m_bounceiness;
    }
}

void SlidingSphere::clampAcceleration(Vector3 desiredVelocity,float dt)
{
    float maxSpeedChange = m_accelerationSpeed * dt;

    m_velocity.x = (abs(desiredVelocity.x - m_velocity.x) <= maxSpeedChange) ?
        desiredVelocity.x :
        m_velocity.x + ((desiredVelocity.x - m_velocity.x >= 0) ? 1.0f : -1.0f) * maxSpeedChange;
    m_velocity.z = (abs(desiredVelocity.z - m_velocity.z) <= maxSpeedChange) ?
        desiredVelocity.z :
        m_velocity.z + ((desiredVelocity.z - m_velocity.z >= 0) ? 1.0f : -1.0f) * maxSpeedChange;
}
