#include "snkpch.h"

#include "Engine/Application/Game.h"

namespace SnakeEngine
{
	Game::Game(GameWindowConfiguration pGameWindowConfiguration)
		: mGameWindowConfiguration{ pGameWindowConfiguration }
	{
		mMainWindow = std::make_unique<SnakeEngine::Window>(pGameWindowConfiguration.nameWindow, 
															pGameWindowConfiguration.windowWidth, 
															pGameWindowConfiguration.windowHeight);

		mInstance = this;
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

	Game& Game::getInstance()
	{
		return *mInstance;
	}

	Window& Game::getMainWindowRef() noexcept
	{
		return *mMainWindow;
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
		const float deltaTime = mTimer.getElapsedTime();
		const float maxFPSMs = 1000.0f / mGameWindowConfiguration.maxFPS;

		if (deltaTime < maxFPSMs)
		{
			float delay = maxFPSMs - deltaTime;
			SDL_Delay(static_cast<Uint32>(delay));
		}
	}

}
