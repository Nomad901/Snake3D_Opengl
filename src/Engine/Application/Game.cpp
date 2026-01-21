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
		while (SDL_PollEvent(&mGameComponents.events))
		{
			mGameComponents.imguiLayer->processEvents(mGameComponents.events);
			if (mGameComponents.events.type == SDL_EVENT_QUIT)
				mIsRunning = false;
		}
	}

	void Game::preUpdate()
	{
		ImGui::Begin("name");
		ImGui::SetNextWindowPos(ImVec2(200.0f, 200.0f));
		ImGui::SetNextWindowSize(ImVec2(200.0f, 200.0f));

		ImGui::Button("some buttons");
		ImGui::End();
	}

	void Game::update()
	{
		mGameComponents.mainWindow->render();
	}

	void Game::startFrame()
	{
		mGameComponents.timer.startTimer();
		mGameComponents.imguiLayer->startFrame();
	}

	void Game::stopFrame()
	{
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
