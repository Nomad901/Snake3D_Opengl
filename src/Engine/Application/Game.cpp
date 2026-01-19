#include "snkpch.h"

#include "Engine/Application/Game.h"

namespace SnakeEngine
{
	Game::Game(GameWindowConfiguration pGameWindowConfiguration)
		: mGameWindowConfiguration{ pGameWindowConfiguration }
	{
		mGameComponents.mainWindow = new Window(pGameWindowConfiguration.nameWindow, 
												pGameWindowConfiguration.windowWidth, 
												pGameWindowConfiguration.windowHeight);

		mInstance = this;
	}

	Game::~Game()
	{
		delete mGameComponents.mainWindow;
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

	Window& Game::getWindow() noexcept
	{
		return *mGameComponents.mainWindow;
	}
	
	void Game::preRun()
	{
		mIsRunning = true;
	}

	void Game::input()
	{
		ImGui::Button("some buttons");
	}

	void Game::preUpdate()
	{

	}

	void Game::update()
	{
		mGameComponents.mainWindow->render();
	}

	void Game::startFrame()
	{
		mGameComponents.timer.startTimer();
		mGameComponents.imguiLayer.begin();
	}

	void Game::stopFrame()
	{
		mGameComponents.imguiLayer.end();

		const float deltaTime = mGameComponents.timer.getElapsedTime();
		const float maxFPSMs = 1000.0f / mGameWindowConfiguration.maxFPS;

		if (deltaTime < maxFPSMs)
		{
			float delay = maxFPSMs - deltaTime;
			SDL_Delay(static_cast<Uint32>(delay));
		}
	}

}
