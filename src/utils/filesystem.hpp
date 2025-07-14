#pragma once

#include <string>
#include <filesystem>

namespace fs = std::filesystem;

    namespace fsutils {

        bool create_dir(const fs::path& path);
        bool copy_directory(const fs::path& src, const fs::path& dst);
        bool dir_exists_and_not_empty(const fs::path& path);
        std::string timestamp();

    }
