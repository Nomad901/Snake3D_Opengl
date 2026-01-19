#include "snkpch.h"

#include "Engine/Imgui/ImGuiLayer.h"
#include "Engine/Application/Game.h"

#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

namespace SnakeEngine
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGui layer")
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.IniFilename = nullptr;

		ImGui::StyleColorsDark();

		SDL_Window& window = Game::getInstance().getMainWindowRef().getWindow();
		SDL_GLContext* context = &Game::getInstance().getMainWindowRef().getContext();
		ImGui_ImplSDL3_InitForOpenGL(&window, context);
		ImGui_ImplOpenGL3_Init("#version 440");
	}
	ImGuiLayer::~ImGuiLayer()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
	}
	void ImGuiLayer::begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		Window& window = Game::getInstance().getMainWindowRef();
		io.DisplaySize = ImVec2(window.getWindowWidth(), window.getWindowHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}