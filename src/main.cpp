#include "Engine/Application/Window.h"

int32_t main()
{
	Window window("Snake3D", 1280, 720);
	
	while (true)
	{
		window.render();
	}
}