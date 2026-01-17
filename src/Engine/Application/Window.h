#pragma once
#include <iostream>
#include <string>

#include "SDL3/SDL.h"
#include "glad/glad.h"

class Window
{
public:
	Window(std::string_view pWindowName, uint32_t pWindowWidth, uint32_t pWindowHeight);
	~Window();

	void changeWindowSize(uint32_t pWindowWidth, uint32_t pWindowHeight);
	bool isWindowSizeWasChanged() const noexcept;

	void render();

	const SDL_Window* getWindow() noexcept;
	const SDL_GLContext& getContext() noexcept;
	const std::string& getWindowName() const noexcept;

private:
	void init();

#ifdef SNAKE_DEBUG
	static void debugCallBack(GLenum source, GLenum type, GLuint id,
							  GLenum severity, GLsizei length, 
							  const GLchar* message, const void* userParam);
#endif //SNAKE_DEBUG

private:
	bool mWindowSizeWasChanged{ true };

	uint32_t mWindowWidth{ 1280 }, mWindowHeight{ 720 };
	std::string mWindowName{};

	SDL_Window* mWindow;
	SDL_GLContext mContext;
};

