#include "list_env.hpp"
#include <iostream>
#include <filesystem>
#include <chrono>
#include <format>

namespace fs = std::filesystem;

namespace list_env {

    fs::path get_envs_base() {
        const char* home_c = std::getenv("HOME");
        if (!home_c) {
            std::cerr << "Error: HOME environment variable not set.\n";
            std::exit(1);
        }
        return fs::path(home_c) / "devbox" / "envs";
    }

    void list_all() {
        fs::path base = get_envs_base();

        if (!fs::exists(base) || !fs::is_directory(base)) {
            std::cout << "No environments found.\n";
            return;
        }

        std::cout << "Available environments:\n";

        for (const auto& entry : fs::directory_iterator(base)) {
            if (!entry.is_directory()) continue;

            auto ftime = fs::last_write_time(entry);
            auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                ftime - fs::file_time_type::clock::now() + std::chrono::system_clock::now());

            std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);

            std::cout << "  " << entry.path().filename().string()
                    << "  (Last Modified: " << std::put_time(std::localtime(&cftime), "%F %T") << ")\n";
        }
    }

}
