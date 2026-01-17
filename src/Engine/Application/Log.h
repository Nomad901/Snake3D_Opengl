#pragma once
#include <memory>

#include "spdlog/spdlog.h"

namespace SnakeEngine
{
	class Log
	{
	public:
		static auto init() -> void;

		static auto getGameLogger() -> std::shared_ptr<spdlog::logger>&;

	private:
		static inline std::shared_ptr<spdlog::logger> mGameLogger = nullptr;
	};
}

#define GAME_TRACE(...) ::SnakeEngine::log::getGameLoger()->trace(__VA_ARGS__)
