#include <gtest/gtest.h>

#include <filesystem>
#include <optional>
#include <cstdlib>

#include "../src/utils/template_manager.hpp"
#include "../src/commands/new_env.hpp"

namespace fs = std::filesystem;

TEST(TemplateManagerTest, BootstrapsTemplates) {
    template_manager::bootstrap_templates_if_needed();

    const char* home_c = std::getenv("HOME");
    ASSERT_NE(home_c, nullptr);

    fs::path templates_path = fs::path(home_c) / "devbox" / "templates";
    ASSERT_TRUE(fs::exists(templates_path));
    ASSERT_TRUE(fs::is_directory(templates_path));
    ASSERT_FALSE(fs::is_empty(templates_path));
}

// Helper to test new_env::create for a given language
void test_language_env(const std::string& lang) {
    std::optional<fs::path> env_path = new_env::create(lang);
    ASSERT_TRUE(env_path.has_value()) << "Failed to create environment for: " << lang;

    fs::path env = env_path.value();

    ASSERT_TRUE(fs::exists(env)) << "Environment path missing for " << lang;
    ASSERT_TRUE(fs::is_directory(env)) << "Environment path not directory for " << lang;

    bool has_files = false;
    for (auto& p : fs::recursive_directory_iterator(env)) {
        if (fs::is_regular_file(p.path())) {
            has_files = true;
            break;
        }
    }
    ASSERT_TRUE(has_files) << "No files found in created environment for " << lang;
}

TEST(NewEnvTest, CreateEnvsForAllLanguages) {
    const std::vector<std::string> langs = {
        "c",
        "cpp",
        "python",
        "rust",
        "node",
        "ts"
    };

    for (const auto& lang : langs) {
        SCOPED_TRACE("Language: " + lang);
        test_language_env(lang);
    }
}

TEST(NewEnvTest, UnsupportedLanguageReturnsNullopt) {
    std::optional<fs::path> env_path = new_env::create("unsupported_lang_xyz");
    ASSERT_FALSE(env_path.has_value());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
