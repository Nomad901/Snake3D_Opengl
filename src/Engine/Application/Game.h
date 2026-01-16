#pragma once
#include <iostream>

class Game
{
public:
	Game(int32_t pWindowWidth, int32_t pWindowHeight);
	Game() = default;
	~Game();
	 
	void init();
	void run();

private:
	int32_t mWindowWidth, mWindowHeight;

};

