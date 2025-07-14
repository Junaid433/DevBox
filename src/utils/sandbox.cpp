#include "sandbox.hpp"
#include <iostream>
#include <cstdlib>
#include <string>

namespace sandbox {

    int run_in_sandbox(std::string_view rootfs_path, std::string_view shell) {
        
        std::string cmd = 
            "bwrap "
            "--bind " + std::string(rootfs_path) + " /sandbox "
            "--dev /dev "
            "--proc /proc "
            "--tmpfs /tmp "
            "--setenv HOME /sandbox "
            "--chdir /sandbox " +
            std::string(shell);

        std::cout << "Running sandbox command:\n" << cmd << "\n";

        int ret = std::system(cmd.c_str());

        if (ret != 0) {
            std::cerr << "bubblewrap failed or not installed. Trying firejail fallback...\n";

            cmd = "firejail --private=" + std::string(rootfs_path) + " " + std::string(shell);
            std::cout << "Running sandbox fallback command:\n" << cmd << "\n";

            ret = std::system(cmd.c_str());
        }

        return ret;
    }

}
