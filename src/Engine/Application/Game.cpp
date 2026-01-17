#include "Engine/Application/Game.h"

Game::Game(int32_t pWindowWidth, int32_t pWindowHeight)
{
	mMainWindow = std::make_unique<Window>("Snake3D", pWindowWidth, pWindowHeight);
}

void Game::run()
{
	preRun();
	while (mIsRunning)
	{
		mTimer.startTimer();
		input();
		preUpdate();
		update();
		mTimer.stopTimer();
		std::cout << std::format("Timer delta time: {}\n", mTimer.getDeltaTime());
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
