# Compiling a C++ Project with Makefile

This guide will help you compile this C++ project on Linux using its Makefile. Makefiles are used to automate the build process of a project. They contain rules that specify how to compile the project, which files to compile, and how to link them together.

All commands are to be run in the terminal. If you are using Windows, you can use the terminal inside Visual Studio Code while being connected to [WSL](https://learn.microsoft.com/en-us/windows/wsl/install) (Windows Subsystem for Linux). You need the [WSL extension](https://learn.microsoft.com/en-us/windows/wsl/tutorials/wsl-vscode) for this.

## Prerequisites

1. **C++ Compiler**: Ensure you have a C++ compiler installed on your system. The GCC compiler is recommended. If you don't have it, install it with the following commands:

    - Ubuntu / Debian:

    ```bash
    sudo apt update
    sudo apt install build-essential
    ```

    - Arch Linux:

    ```bash
    sudo pacman -Syy base-devel
    ```

2. **Make Tool**: The `make` tool helps in managing and building projects automatically. It is usually bundled with most Unix-like systems.

    - Ubuntu / Debian:

    ```bash
    sudo apt install make
    ```

    - Arch Linux:

    ```bash
    sudo pacman -S make
    ```

## Compiling the Project

To compile this project, navigate to its root directory:

```bash
cd path/to/se-lab1
```

> Replace `path/to/se-lab1` with the actual path to the project directory.

Once inside the project directory, run the `make` command:

```bash
make
```

This will start the compilation process. If your project consists of multiple files, Make will compile only those files which were changed from the last compile, which saves time. If there are errors during the process, they will be displayed in the terminal.

## Running the Project

After successful compilation, an executable file is generated. To run this file, use the `./` command followed by the file's name:

```bash
./output/main
```

Congratulations! You have compiled and run your C++ project with a Makefile.
