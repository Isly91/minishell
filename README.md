# Minishell

## Project Description

**Minishell** is a simple shell program developed as part of the 42 Codam curriculum. The goal of the project is to create a basic Unix shell that mimics the behavior of more advanced shells, such as **bash** or **zsh**, with a focus on implementing essential features like command parsing, environment variables, piping, redirection, and more.

The project includes:

- Command parsing
- Built-in commands like `cd`, `pwd`, `echo`, `exit`, etc.
- Environment variable manipulation (`export`, `unset`, `env`)
- Input and output redirection
- Pipe management
- Signal handling (e.g., `SIGINT` for Ctrl+C)

## Features

- **Basic Shell Functionality**: Run commands, handle arguments, and return exit status.
- **Pipes & Redirection**: Supports piping between commands and redirection for input and output.
- **Environment Management**: Implements `env`, `export`, and `unset` commands.
- **Built-in Commands**: Implements essential commands like `echo`, `cd`, and `exit`.
- **Signal Handling**: Proper handling of `SIGINT` (Ctrl+C) and other signals.
  
## Installation & Setup

To run **minishell**, follow these steps:

### Requirements:

- **GCC** or any C compiler
- **Readline library** (for command-line editing)
  - Install on **macOS**:
    ```bash
    brew install readline
    ```
  - Install on **Linux**:
    ```bash
    sudo apt-get install libreadline-dev
    ```

### Steps to Install:

1. Clone the repository:
    ```bash
    git clone https://github.com/Isly91/minishell.git
    cd minishell
    ```

2. Build the project with `make`:
    ```bash
    make
    ```

3. Run **minishell**:
    ```bash
    ./minishell
    ```

4. Clean the project (removes object files and executable):
    ```bash
    make clean
    ```

5. Fully clean the project:
    ```bash
    make fclean
    ```

6. Rebuild the project:
    ```bash
    make re
    ```

## Usage

Once **minishell** is running, you can enter commands like in a typical Unix shell. Here are some examples:

- **Basic commands**:
    ```bash
    ls
    pwd
    echo "Hello, World!"
    ```

- **Built-in commands**:
    ```bash
    cd /path/to/directory
    exit
    echo "This is a message"
    ```

- **Redirection**:
    - Redirect output to a file:
        ```bash
        echo "Hello" > output.txt
        ```

    - Redirect error output to a file:
        ```bash
        echo "Error" 2> error.txt
        ```

- **Pipes**:
    - Pipe output from one command to another:
        ```bash
        cat file.txt | grep "pattern"
        ```

- **Environment variables**:
    - Set an environment variable:
        ```bash
        export VAR=value
        ```

    - Unset an environment variable:
        ```bash
        unset VAR
        ```

