#pragma once

#include <string_view>
#include <optional>
#include <filesystem>

namespace new_env { 
    std::optional<std::filesystem::path> create(std::string_view lang);
}
