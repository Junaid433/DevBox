#pragma once
#include <string_view>
#include "../utils/config.hpp"

namespace enter_env { void enter(std::string_view lang, const config::Settings& settings); }
