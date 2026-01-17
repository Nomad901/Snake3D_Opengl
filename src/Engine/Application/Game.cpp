#include "snkpch.h"

#include "Engine/Application/Game.h"

Game::Game(uint32_t pWindowWidth, uint32_t pWindowHeight, float pMaxFPS)
{
	mMainWindow = std::make_unique<SnakeEngine::Window>("Snake3D", pWindowWidth, pWindowHeight);
	mMaxFPS = pMaxFPS;
}

void Game::run()
{
	preRun();
	while (mIsRunning)
	{
		startFrame();

		input();
		preUpdate();
		update();

		stopFrame();
	}
}

bool Game::isRunning() noexcept
{
	return mIsRunning;
}

void Game::preRun()
{
	mIsRunning = true;
}

void Game::input()
{

}

void Game::preUpdate()
{

}

void Game::update()
{
	mMainWindow->render();
}

void Game::startFrame()
{
	mTimer.startTimer();
}

void Game::stopFrame()
{
	mTimer.stopTimer();

	const float deltaTime = mTimer.getDeltaTime();
	const float maxFPSMs = 1000.0f / mMaxFPS;

	if (deltaTime < maxFPSMs)
	{
		float delay = maxFPSMs - deltaTime;
		SDL_Delay(static_cast<Uint32>(delay));
	}
}
