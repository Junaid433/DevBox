#include "config.hpp"
#include <optional>

namespace config {

    std::optional<Settings> load() {
        return std::nullopt;
    }

    bool save(const Settings&) {
        return true;
    }

    std::string config_file_path() {
        return "";
    }

} 
