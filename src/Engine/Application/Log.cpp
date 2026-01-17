#include "snkpch.h"

#include "Engine/Application/Log.h"

#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace SnakeEngine
{
	auto SnakeEngine::Log::init() -> void
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		mGameLogger = spdlog::stdout_color_mt("GAME");
		mGameLogger->set_level(spdlog::level::trace);
	}

	auto SnakeEngine::Log::getGameLogger() -> std::shared_ptr<spdlog::logger>&
	{
		return mGameLogger;
	}
}
