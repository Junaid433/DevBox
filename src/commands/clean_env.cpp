#include "clean_env.hpp"
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

namespace fs = std::filesystem;

namespace clean_env {

    fs::path get_envs_base() {
        const char* home_c = std::getenv("HOME");
        if (!home_c) {
            std::cerr << "Error: HOME environment variable not set.\n";
            std::exit(1);
        }
        return fs::path(home_c) / "devbox" / "envs";
    }

    std::vector<fs::path> find_envs(std::string_view lang) {
        fs::path base = get_envs_base();
        std::vector<fs::path> results;

        if (!fs::exists(base)) {
            return results;
        }

        for (const auto& entry : fs::directory_iterator(base)) {
            if (!entry.is_directory()) continue;
            std::string dirname = entry.path().filename().string();
            if (dirname.find(std::string(lang)) == 0) {
                results.push_back(entry.path());
            }
        }

        return results;
    }

    void remove(std::string_view lang) {
        auto envs = find_envs(lang);
        if (envs.empty()) {
            std::cout << "No environments found for language: " << lang << "\n";
            return;
        }

        std::cout << "Found environments for " << lang << ":\n";
        for (size_t i = 0; i < envs.size(); ++i) {
            std::cout << " [" << i << "] " << envs[i] << "\n";
        }

        std::cout << "Removing all environments for language: " << lang << "\n";

        for (const auto& path : envs) {
            std::error_code ec;
            fs::remove_all(path, ec);
            if (ec) {
                std::cerr << "Failed to remove " << path << ": " << ec.message() << "\n";
            } else {
                std::cout << "Removed " << path << "\n";
            }
        }
    }

}
