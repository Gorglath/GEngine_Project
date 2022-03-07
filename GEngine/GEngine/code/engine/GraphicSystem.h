#pragma once

#include "OgreOverlayPrerequisites.h"
#include "OgrePrerequisites.h"

#include "BaseSystem.h"

#include "GameObjectManager.h"
#include "OgreColourValue.h"
#include "OgreOverlaySystem.h"
#include "SdlEmulationLayer.h"
#include "System/StaticPluginLoader.h"
#include "Threading/OgreUniformScalableTask.h"

using namespace Ogre;

class SdlInputHandler;

class GraphicSystem : public BaseSystem, public Ogre::UniformScalableTask
{
    void createCamera() override
    {
        mCamera = mSceneManager->createCamera("Main Camera");
        mCamera->setPosition(Ogre::Vector3(0, 20, 0));
        // Look back along -Z
        mCamera->lookAt(Ogre::Vector3(0, 0, 0));

        mCamera->rotate(Ogre::Vector3(0, 1, 0), Radian(Degree(180.0f)));
        mCamera->setNearClipDistance(0.2f);
        mCamera->setFarClipDistance(1000.0f);
        mCamera->setAutoAspectRatio(true);
    }
public:
    GraphicSystem() {}
    GraphicSystem(GameState* gameState) : GraphicsSystem(gameState) {}
};