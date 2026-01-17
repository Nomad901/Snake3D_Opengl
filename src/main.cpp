#include "Engine/Application/Game.h"

int32_t main()
{
	uint32_t windowWidth = 1280;
	uint32_t windowHeight = 720;
	float fpsRate = 144.0f;

	Game game(windowWidth, windowHeight, fpsRate);
	game.run();
}