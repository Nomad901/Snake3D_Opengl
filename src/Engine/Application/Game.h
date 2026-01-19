#pragma once
#include "Engine/Application/Window.h"
#include "Engine/Application/Timer.h"
#include "Engine/Imgui/ImGuiLayer.h"

namespace SnakeEngine
{
	struct GameWindowConfiguration
	{
		uint32_t windowWidth{ 1280 }, windowHeight{ 720 };
		float maxFPS{ 144.0f };
		std::string nameWindow{ "Snake3D" };
	};

	struct GameComponents
	{
		Window* mainWindow;
		ImGuiLayer* imguiLayer;
		SnakeEngine::Timer timer;
	};

	class Game
	{
	public:
		Game(GameWindowConfiguration pGameConfiguration);
		~Game();
	 
		void run();

		bool isRunning() noexcept;

		static Game& getInstance();
		Window& getWindow() noexcept;

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
		GameComponents mGameComponents;

		static inline Game* mInstance = nullptr;
	};
}

