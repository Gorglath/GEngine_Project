#include "SlidingSphereGame.h"

void SlidingSphereGame::createScene01()
{/*
	createFloor();
	createLight();*/

	/*m_sphere.createSphere(m_sceneManager);*/

	GameState::createScene01();
}

void SlidingSphereGame::update(float dt)
{
	m_sphere.update(dt,m_inputData);
}

void SlidingSphereGame::keyPressed(const SDL_KeyboardEvent& arg)
{
    if (arg.keysym.scancode == SDL_SCANCODE_W)
        m_inputData.m_isWKeyPressed = true;
    else if (arg.keysym.scancode == SDL_SCANCODE_A)
        m_inputData.m_isAKeyPressed = true;
    else if (arg.keysym.scancode == SDL_SCANCODE_S)
        m_inputData.m_isSKeyPressed = true;
    else if (arg.keysym.scancode == SDL_SCANCODE_D)
        m_inputData.m_isDKeyPressed = true;
}

void SlidingSphereGame::keyReleased(const SDL_KeyboardEvent& arg)
{
    if (arg.keysym.scancode == SDL_SCANCODE_W)
        m_inputData.m_isWKeyPressed = false;
    else if (arg.keysym.scancode == SDL_SCANCODE_A)
        m_inputData.m_isAKeyPressed = false;
    else if (arg.keysym.scancode == SDL_SCANCODE_S)
        m_inputData.m_isSKeyPressed = false;
    else if (arg.keysym.scancode == SDL_SCANCODE_D)
        m_inputData.m_isDKeyPressed = false;
}
