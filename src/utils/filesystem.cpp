#include "filesystem.hpp"
#include <iostream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

namespace fsutils {

    bool create_dir(const fs::path& path) {
        std::error_code ec;
        if (!std::filesystem::create_directories(path, ec)) {
            if (ec) {
                std::cerr << "Error creating directory " << path << ": " << ec.message() << "\n";
                return false;
            }
        }
        return true;
    }

    bool copy_directory(const fs::path& src, const fs::path& dst) {
        std::error_code ec;
        if (!fs::exists(src)) {
            std::cerr << "Source directory does not exist: " << src << "\n";
            return false;
        }

        for (const auto& entry : fs::recursive_directory_iterator(src, ec)) {
            if (ec) {
                std::cerr << "Error iterating directory: " << ec.message() << "\n";
                return false;
            }
            const auto& path = entry.path();
            auto relative_path = fs::relative(path, src);
            fs::path target_path = dst / relative_path;

            if (entry.is_directory()) {
                if (!create_dir(target_path))
                    return false;
            } else if (entry.is_regular_file()) {
                fs::copy_file(path, target_path, fs::copy_options::overwrite_existing, ec);
                if (ec) {
                    std::cerr << "Failed to copy file: " << path << " : " << ec.message() << "\n";
                    return false;
                }
            }
        }
        return true; 
    }

    bool dir_exists_and_not_empty(const fs::path& path) {
    std::error_code ec;
    if (!fs::exists(path, ec) || !fs::is_directory(path, ec)) {
        return false;
    }
    auto it = fs::directory_iterator(path, ec);
    return it != fs::end(it);
    }

    std::string timestamp() {
        using namespace std::chrono;
        auto now = system_clock::now();
        std::time_t t = system_clock::to_time_t(now);
        std::tm tm;
        localtime_r(&t, &tm);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
        return oss.str();
    }

}  
