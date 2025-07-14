#include "enter_env.hpp"
#include "../utils/config.hpp"
#include "../utils/filesystem.hpp"
#include "../utils/sandbox.hpp"
#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>

namespace fs = std::filesystem;

namespace enter_env {

    fs::path get_envs_base() {
        const char* home_c = std::getenv("HOME");
        if (!home_c) {
            std::cerr << "Error: HOME environment variable not set.\n";
            std::exit(1);
        }
        return fs::path(home_c) / "devbox" / "envs";
    }

    void enter(std::string_view lang, const config::Settings& settings) {
        fs::path base = get_envs_base();

        fs::path latest_env;
        std::chrono::file_clock::time_point latest_time;

        bool found = false;

        for (const auto& entry : fs::directory_iterator(base)) {
            if (!entry.is_directory()) continue;
            std::string dirname = entry.path().filename().string();
            if (dirname.find(std::string(lang)) == 0) {
                auto ftime = fs::last_write_time(entry);
                if (!found || ftime > latest_time) {
                    latest_time = ftime;
                    latest_env = entry.path();
                    found = true;
                }
            }
        }

        if (!found) {
            std::cerr << "No environment found for language: " << lang << "\n";
            return;
        }

        std::cout << "Entering environment: " << latest_env << "\n";

        std::string shell = settings.default_shell.empty() ? "/bin/bash" : settings.default_shell;

        if (settings.sandbox_enabled) {
            int ret = sandbox::run_in_sandbox(latest_env.string(), shell);
            if (ret != 0) {
                std::cerr << "Sandboxed shell exited with code " << ret << "\n";
            }
        } else {
            std::cout << "Launching shell without sandbox...\n";
            int ret = std::system((shell + " --rcfile " + latest_env.string()).c_str());
            if (ret != 0) {
                std::cerr << "Shell exited with code " << ret << "\n";
            }
        }
    }

}
