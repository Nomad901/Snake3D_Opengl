#include "snkpch.h"

#include "Engine/Imgui/ImGuiLayer.h"
#include "Engine/Application/Game.h"

namespace SnakeEngine
{
	ImGuiLayer::ImGuiLayer(Window& pWindow)
		: Layer("ImGui layer")
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.IniFilename = nullptr;

		ImGui::StyleColorsDark();

		ImGui_ImplSDL3_InitForOpenGL(&pWindow.getWindow(), pWindow.getContext());
		ImGui_ImplOpenGL3_Init("#version 440");

		mWindowWidth  = pWindow.getWindowWidth();
		mWindowHeight = pWindow.getWindowHeight();
	}
	ImGuiLayer::~ImGuiLayer()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
	}
	void ImGuiLayer::processEvents(SDL_Event& pEvents)
	{
		ImGui_ImplSDL3_ProcessEvent(&pEvents);
	}
	void ImGuiLayer::startFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
	}
	void ImGuiLayer::endFrame()
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(mWindowWidth, mWindowHeight);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}