#pragma once
#include <iostream>
#include <memory>

#include "Engine/Application/Window.h"
#include "Engine/Application/Timer.h"

class Game
{
public:
	Game(uint32_t pWindowWidth, uint32_t pWindowHeight, float pMaxFPS);
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

	float mMaxFPS{ 144.0f };
	
	std::unique_ptr<Window> mMainWindow;
	Timer mTimer;
};

