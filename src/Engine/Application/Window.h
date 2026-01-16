#pragma once
#include <iostream>

#include "SDL3/SDL.h"
#include "glad/glad.h"

class Window
{
public:
	Window(int32_t pWindowWidth, int32_t pWindowHeight);
	~Window();

	void changeWindowSize(int32_t pWindowWidth, int32_t pWindowHeight);
	bool isWindowSizeWasChanged() const noexcept;

	void render();

	const SDL_Window* getWindow() noexcept;
	const SDL_GLContext& getContext() noexcept;

private:
	void init();

private:
	bool mWindowSizeWasChanged{ true };

	int32_t mWindowWidth{ 1280 }, mWindowHeight{ 720 };

	SDL_Window* mWindow;
	SDL_GLContext mContext;
};

