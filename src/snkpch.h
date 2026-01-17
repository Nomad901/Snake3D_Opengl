#pragma once

#include <iostream>
#include <sstream>
#include <fstream>

#include <format>
#include <algorithm>
#include <memory>
#include <utility>
#include <functional>
#include <filesystem>

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include <chrono>
#include <mutex>

#include "SDL3/SDL.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"

#ifdef SNAKE_PLATFORM_WINDOWS
	#include <Windows.h>
#endif // SNAKE_PLATFORM_WINDOWS