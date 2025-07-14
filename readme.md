
---
```
DevBox - Per-Language Development Environment Manager
====================================================

Overview
--------
DevBox is a lightweight CLI tool to quickly create, manage, and enter isolated development environments for various programming languages. It uses template projects and sandboxing techniques to help developers maintain clean and reproducible setups per language or project.

Key Features
------------
- Create new language-specific environments from templates
- Automatically bootstrap templates if not present
- Supports Python (with venv), Rust (with rustup), Node.js, C, C++, TypeScript, and more
- Enter existing environments easily
- List and clean environments
- Optionally open environment folder in your preferred editor after creation
- Configurable via a settings file (~/.config/devbox/config.ini)
- Portable and simple, relying on standard tools and minimal dependencies

Project Structure

├── devbox                    # Compiled CLI binary
├── src                       # Source code
│   ├── commands              # CLI commands implementations
│   ├── utils                 # Utility modules (filesystem, sandbox, config, templates)
│   └── main.cpp              # CLI entrypoint
├── templates                 # Language-specific template projects
│   ├── c
│   ├── cpp
│   ├── node
│   ├── python
│   ├── rust
│   └── ts
└── tests                     # Unit tests (GoogleTest framework)

Installation
------------
1. Clone the repository:
   git clone https://github.com/yourusername/devbox.git
2. Create build directory and compile:
   mkdir build && cd build
   cmake ..
   make
3. (Optional) Install globally:
   sudo make install

Usage
-----
Basic syntax:

  devbox <command> <language> [options]

Commands:

  new <language> [--open|-o]   Create a new environment for the specified language.
                               --open flag opens the environment folder in the editor.

  enter <language>             Enter the existing environment for the language.

  list                        List all available environments.

  clean <language>            Remove the environment for the specified language.

  help                        Show this usage message.

Example:

  devbox new python --open

This creates a new Python virtual environment from the template and opens it in your editor.

Configuration
-------------
DevBox loads configuration from `~/.config/devbox/config.ini`. Example config:

  [settings]
  editor=code            ; Editor command to open environment folders
  cache_dir=~/.cache/devbox   ; Directory to store environments and templates

If no editor is specified, DevBox attempts to use the $EDITOR environment variable or defaults to `code`.

Templates
---------
Templates are stored under the templates directory and bootstrapped to the cache directory automatically on first run:

  ~/.cache/devbox/templates/

Each template folder contains starter files, e.g.,

  python/
    main.py
    requirements.txt

  node/
    index.js
    package.json

You can customize or add your own templates.

Development
-----------
- Source code is under `src/`.
- Tests use GoogleTest framework, located in `tests/`.
- Use CMake to build and test.

Contributing
------------
Contributions are welcome! Feel free to open issues or submit pull requests.
```
---


