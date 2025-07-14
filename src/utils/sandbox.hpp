#pragma once
#include <string_view>

namespace sandbox {
    int run_in_sandbox(std::string_view rootfs_path, std::string_view shell = "/bin/bash");
}
