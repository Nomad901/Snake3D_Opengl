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

#define GAME_TRACE(...) ::SnakeEngine::Log::getGameLogger()->trace(__VA_ARGS__)
#define GAME_INFO(...)  ::SnakeEngine::Log::getGameLogger()->info(__VA_ARGS__)
#define GAME_WARN(...)  ::SnakeEngine::Log::getGameLogger()->warn(__VA_ARGS__)
#define GAME_ERROR(...) ::SnakeEngine::Log::getGameLogger()->error(__VA_ARGS__)
#define GAME_FATAL(...) ::SnakeEngine::Log::getGameLogger()->fatal(__VA_ARGS__)
