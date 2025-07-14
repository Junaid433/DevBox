#include "template_manager.hpp"
#include "filesystem.hpp"

#include <cstdlib>      
#include <filesystem>
#include <iostream>
#include <cstdlib>      

namespace fs = std::filesystem;

namespace template_manager {

    void bootstrap_templates_if_needed() {
        const char* home_c = std::getenv("HOME");
        if (!home_c) {
            std::cerr << "Error: HOME environment variable not set.\n";
            std::exit(1);
        }
        fs::path home = home_c;
        fs::path cache_templates_dir = home / ".cache" / "devbox" / "templates";

        if (fsutils::dir_exists_and_not_empty(cache_templates_dir)) {
            return;
        }

        fs::path repo_templates = fs::current_path() / "templates";

        if (!fs::exists(repo_templates)) {
            std::cerr << "Error: Built-in templates directory missing: " << repo_templates << "\n";
            std::exit(1);
        }

        std::cout << "Bootstrapping templates to " << cache_templates_dir << " ...\n";

        if (!fsutils::copy_directory(repo_templates, cache_templates_dir)) {
            std::cerr << "Failed to bootstrap templates\n";
            std::exit(1);
        }
    }

}
