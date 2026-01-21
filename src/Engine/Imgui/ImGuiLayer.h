#pragma once

#include "Engine/Application/Layer.h"
#include "Engine/Application/Window.h"

namespace SnakeEngine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(Window& pWindow);
		~ImGuiLayer();

		virtual void onUpdate(float pDeltaTime) override {}
		virtual void onImGuiRender() override {}

		void processEvents(SDL_Event& pEvents);
		void startFrame();
		void endFrame();
	private:
		uint32_t mWindowWidth, mWindowHeight;
	};
}