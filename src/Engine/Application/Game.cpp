#include "snkpch.h"

#include "Engine/Application/Game.h"

namespace SnakeEngine
{
	Game::Game(const GameWindowConfiguration& pGameWindowConfiguration)
		: mGameWindowConfiguration{ pGameWindowConfiguration }
	{
		mGameComponents.mainWindow = std::make_unique<Window>(pGameWindowConfiguration.nameWindow, 
															  pGameWindowConfiguration.windowWidth, 
															  pGameWindowConfiguration.windowHeight);
		mGameComponents.imguiLayer = std::make_unique<ImGuiLayer>(*mGameComponents.mainWindow.get());
	}

	void Game::run()
	{
		preRun();
		while (mIsRunning)
		{
			startFrame();

			input();
			preUpdate();

			stopFrame();

			update();
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
		while (SDL_PollEvent(&mGameComponents.events))
		{
			mGameComponents.imguiLayer->processEvents(mGameComponents.events);
			if (mGameComponents.events.type == SDL_EVENT_QUIT)
				mIsRunning = false;
		}
	}

	void Game::preUpdate()
	{
		glClearColor(0.2f, 0.2f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Game::update()
	{
		mGameComponents.mainWindow->render();
	}

	void Game::startFrame()
	{
		mGameComponents.timer.startTimer();
	}

	void Game::stopFrame()
	{
		mGameComponents.imguiLayer->startFrame();

		ImGui::Begin("name");
		ImGui::Text("smth");
		ImGui::End();

		mGameComponents.imguiLayer->endFrame();

		const float deltaTime = mGameComponents.timer.getElapsedTime();
		const float maxFPSMs = mGameWindowConfiguration.maxFPS > 0 ? 
							   1000.0f / mGameWindowConfiguration.maxFPS :
							   0.0f;

		if (deltaTime < maxFPSMs)
		{
			float delay = maxFPSMs - deltaTime;
			SDL_Delay(static_cast<Uint32>(delay));
		}
	}
}
