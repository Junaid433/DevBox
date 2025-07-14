#include "new_env.hpp"
#include "../utils/filesystem.hpp"
#include <iostream>
#include <cstdlib>  
#include <filesystem>
#include "../utils/sandbox.hpp"  
#include <optional> 

namespace fs = std::filesystem;

namespace new_env {

    std::optional<fs::path> create(std::string_view lang) {
        const char* home_c = std::getenv("HOME");
        if (!home_c) {
            std::cerr << "Error: HOME environment variable not set.\n";
            return std::nullopt;
        }
        fs::path home = home_c;
        fs::path base_dir = home / "devbox" / "envs";
        std::string ts = fsutils::timestamp();
        std::string env_name = std::string(lang) + "-" + ts;
        fs::path env_path = base_dir / env_name;

        if (!fsutils::create_dir(env_path)) {
            std::cerr << "Failed to create environment directory: " << env_path << "\n";
            return std::nullopt;
        }

        fs::path template_path = home / ".cache" / "devbox" / "templates" / lang;
        if (!fs::exists(template_path)) {
            std::cerr << "Template not found for language: " << lang << "\n";
            return std::nullopt;
        }

        if (!fsutils::copy_directory(template_path, env_path)) {
            std::cerr << "Failed to copy template files to environment\n";
            return std::nullopt;
        }

        if (lang == "python") {
            std::string cmd = "python3 -m venv " + (env_path / "venv").string();
            std::cout << "Creating Python virtual environment...\n";
            int ret = std::system(cmd.c_str());
            if (ret != 0) {
                std::cerr << "Failed to create Python venv\n";
                return std::nullopt;
            }
        } else if (lang == "rust") {
            std::string cmd = 
                "curl https://sh.rustup.rs -sSf | sh -s -- -y "
                "--default-toolchain stable --no-modify-path "
                "--profile minimal --default-host $(uname -m)-unknown-linux-gnu "
                "--prefix " + env_path.string();
            std::cout << "Installing Rust toolchain...\n";
            int ret = std::system(cmd.c_str());
            if (ret != 0) {
                std::cerr << "Failed to install Rust toolchain\n";
                return std::nullopt;
            }
        } else {
            std::cerr << "Unsupported language: " << lang << "\n";
            return std::nullopt;
        }

        std::cout << "[+] Environment created at: " << env_path << "\n";
        return env_path;
    }

}
