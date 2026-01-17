#include <format>

#include "Engine/Application/Window.h"
#include "Engine/Application/Log.h"

Window::Window(std::string_view pWindowName, int32_t pWindowWidth, int32_t pWindowHeight)
{
	mWindowWidth = pWindowWidth;
	mWindowHeight = pWindowHeight;
	mWindowName = pWindowName;

	init();
}

Window::~Window()
{
	SDL_GL_DestroyContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Window::changeWindowSize(int32_t pWindowWidth, int32_t pWindowHeight)
{
	mWindowWidth = pWindowWidth;
	mWindowHeight = pWindowHeight;

	mWindowSizeWasChanged = true;
}

bool Window::isWindowSizeWasChanged() const noexcept
{
	return mWindowSizeWasChanged;
}

void Window::render()
{
}

const SDL_Window* Window::getWindow() noexcept
{
	return mWindow;
}

const SDL_GLContext& Window::getContext() noexcept
{
	return mContext;
}

const std::string& Window::getWindowName() const noexcept
{
	return mWindowName;
}

void Window::init()
{
	if (!SDL_Init(SDL_INIT_VIDEO))
		GAME_ERROR("Couldnt initialize SDL_VIDEO!");
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	mWindow = SDL_CreateWindow(mWindowName.c_str(), mWindowWidth, mWindowHeight, 
							   SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_RESIZABLE);
	if (!mWindow)
		GAME_ERROR(std::format("Couldnt initialize the Window! Name: {}, size: {}x{}", mWindowName, mWindowWidth, mWindowHeight));
	
	mContext = SDL_GL_CreateContext(mWindow);
	if (!mContext)
		GAME_ERROR(std::format("Couldnt initialize Context! Name: {}, size: {}x{}", mWindowName, mWindowWidth, mWindowHeight));
	
	if (!SDL_GL_MakeCurrent(mWindow, mContext))
		GAME_ERROR(std::format("Couldnt initialize Window+Context! Name: {}, size: {}x{}", mWindowName, mWindowWidth, mWindowHeight));

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
		GAME_ERROR(std::format("Couldnt initialize Glad! Name: {}, size: {}x{}", mWindowName, mWindowWidth, mWindowHeight));

#ifdef SNAKE_DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	
	glDebugMessageCallback(debugCallBack, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif // SNAKE_DEBUG

}

#ifdef SNAKE_DEBUG
void Window::debugCallBack(GLenum source, GLenum type, GLuint id, 
						   GLenum severity, GLsizei length, 
						   const GLchar* message, const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------\n";
	std::cout << "Debug message (" << id << "): " << message << '\n';

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	}
	std::cout << '\n';

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behavior"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behavior"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	}
	std::cout << '\n';

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	}
	std::cout << '\n\n';
}
#endif // SNAKE_DEBUG

