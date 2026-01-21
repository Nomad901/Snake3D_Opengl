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
		std::unique_ptr<Window> mainWindow;
		std::unique_ptr<ImGuiLayer> imguiLayer;
		SnakeEngine::Timer timer;
		SDL_Event events;
	};

	class Game
	{
	public:
		Game(const GameWindowConfiguration& pGameConfiguration);
		~Game() = default;
	 
		void run();

		bool isRunning() noexcept;

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
	};
}

