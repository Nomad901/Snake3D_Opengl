#pragma once

#include "Engine/Application/Layer.h"

namespace SnakeEngine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void onUpdate(float pDeltaTime) override {}
		virtual void onImGuiRender() override {}

		void begin();
		void end();
	};
}