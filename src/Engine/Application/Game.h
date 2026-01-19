#pragma once
#include "Engine/Application/Window.h"
#include "Engine/Application/Timer.h"

namespace SnakeEngine
{
	struct GameWindowConfiguration
	{
		uint32_t windowWidth{ 1280 }, windowHeight{ 720 };
		float maxFPS{ 144.0f };
		std::string nameWindow{ "Snake3D" };
	};

	class Game
	{
	public:
		Game(GameWindowConfiguration pGameConfiguration);
		~Game() = default;
	 
		void run();

		bool isRunning() noexcept;

		static Game& getInstance();
		Window& getMainWindowRef() noexcept;

	private:
		void preRun();
		void input();
		void preUpdate();
		void update();

		// ***************
		// Starts timer for regulation fps;
		// ***************
		void startFrame();
		// ***************
		// Stops timer and regulates fps;
		// ***************
		void stopFrame(); 

	private:
		bool mIsRunning{ false };
		
		GameWindowConfiguration mGameWindowConfiguration;
	
		std::unique_ptr<SnakeEngine::Window> mMainWindow;
		SnakeEngine::Timer mTimer;

		static inline Game* mInstance = nullptr;
	};
}

