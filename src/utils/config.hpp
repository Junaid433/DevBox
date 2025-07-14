#pragma once
#include <string>
#include <optional>

namespace config {

    struct Settings {
        std::string default_shell = "/bin/bash";
        bool sandbox_enabled = true;
        std::string templates_path;
    };

    std::optional<Settings> load();

    bool save(const Settings& settings);

    std::string config_file_path();

}
