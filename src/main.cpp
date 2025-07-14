#include <iostream>       // for std::cout, std::cerr
#include <filesystem>
#include <optional>

#include <string_view>
#include <format>
#include <span>

#include "commands/new_env.hpp"
#include "commands/enter_env.hpp"
#include "utils/template_manager.hpp"
#include "commands/clean_env.hpp"
#include "commands/list_env.hpp"
#include "utils/config.hpp"

void print_usage() {
    std::cout << std::format(
        "Usage:\n"
        "  devbox new <language> [--open]    Create a new dev environment\n"
        "  devbox enter <language>            Enter an existing environment\n"
        "  devbox list                       List all environments\n"
        "  devbox clean <language>           Remove an environment\n"
        "  devbox help                      Show this message\n"
    );
}

int main(int argc, char* argv[]) {
    auto maybe_settings = config::load();
    config::Settings settings = maybe_settings.value_or(config::Settings{});

    template_manager::bootstrap_templates_if_needed();

    std::span args(argv, static_cast<size_t>(argc));

    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string_view cmd = args[1];

    if (cmd == "help") {
        print_usage();
        return 0;
    }

    if (cmd == "list") {
        list_env::list_all();
        return 0;
    }

    if (argc < 3) {
        std::cerr << std::format("Error: Missing language argument for command '{}'\n", cmd);
        print_usage();
        return 1;
    }

    std::string_view lang = args[2];
    bool open_editor = false;

    // Check for optional --open flag after language argument
    if (argc > 3) {
        std::string_view opt = args[3];
        if (opt == "--open" || opt == "-o") {
            open_editor = true;
        }
    }

    if (cmd == "new") {
        std::optional<std::filesystem::path> env_path = new_env::create(std::string(lang));
        if (!env_path) {
            std::cerr << "Failed to create environment.\n";
            return 1;
        }

        if (open_editor) {
            std::string editor_cmd;
            const char* editor_env = std::getenv("EDITOR");
            if (editor_env) {
                editor_cmd = std::string(editor_env) + " " + env_path.value().string();
            } else {
                editor_cmd = "code " + env_path.value().string(); // default to VSCode CLI
            }
            int ret = std::system(editor_cmd.c_str());
            if (ret != 0) {
                std::cerr << "Warning: Failed to open editor\n";
            }
        }
    }
    else if (cmd == "enter") {
        std::cout << std::format("[enter] Enter environment for language: {}\n", lang);
        enter_env::enter(lang, settings);
    }
    else if (cmd == "clean") {
        std::cout << std::format("[clean] Remove environment for language: {}\n", lang);
        clean_env::remove(lang);
    }
    else {
        std::cerr << std::format("Unknown command: {}\n", cmd);
        print_usage();
        return 1;
    }

    return 0;
}
