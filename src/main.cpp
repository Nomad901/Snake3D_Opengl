#include "snkpch.h"

#include "Engine/Application/Game.h"

int32_t main()
{
	SnakeEngine::GameWindowConfiguration gameWindowConfig;
	gameWindowConfig.windowWidth = 1280;
	gameWindowConfig.windowHeight = 720;
	gameWindowConfig.maxFPS = 144.0f;
	gameWindowConfig.nameWindow = "Snake3D";

	SnakeEngine::Game game(gameWindowConfig);
	game.run();
}