#pragma once
#include <iostream>
#include <memory>

#include "Engine/Application/Window.h"
#include "Engine/Application/Timer.h"

class Game
{
public:
	Game(int32_t pWindowWidth, int32_t pWindowHeight);
	~Game() = default;
	 
	void run();

	bool isRunning() noexcept;

private:
	void preRun();
	void input();
	void preUpdate();
	void update();

private:
	bool mIsRunning{ false };

	std::unique_ptr<Window> mMainWindow;
	Timer mTimer;
};

