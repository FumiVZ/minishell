# minishell

<p align="center">
  <img src="https://img.shields.io/badge/42-Lyon-blue?style=for-the-badge&logo=42&logoColor=white" alt="42 Lyon">
  <img src="https://img.shields.io/badge/Score-109%2F100-brightgreen?style=for-the-badge" alt="Score 109/100">
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C">
</p>

## Description

**Minishell** is a simple shell implementation written in C as part of the 42 school curriculum. This project recreates core functionalities of bash, including command execution, pipes, redirections, environment variable management, and built-in commands.

The goal is to understand how a Unix shell works under the hood by implementing parsing, process management, signal handling, and more.

---

## Features

| Feature | Description |
|---------|-------------|
| **Command Execution** | Execute binaries from PATH or absolute/relative paths |
| **Pipes** | Chain commands with `\|` operator |
| **Redirections** | Input `<`, output `>`, append `>>`, heredoc `<<` |
| **Logical Operators** | `&&` and `\|\|` with short-circuit evaluation |
| **Subshells** | Command grouping with parentheses `()` |
| **Environment Variables** | Expansion with `$VAR` and `$?` for exit status |
| **Wildcards** | Pattern matching with `*` and `?` |
| **Quote Handling** | Single `'` and double `"` quotes |
| **Signal Handling** | `Ctrl+C`, `Ctrl+D`, `Ctrl+\` like bash |

---

## Built-in Commands

| Command | Description |
|---------|-------------|
| `echo` | Display text with `-n` option support |
| `cd` | Change directory (supports `-`, `~`, absolute/relative paths) |
| `pwd` | Print current working directory |
| `export` | Set environment variables |
| `unset` | Remove environment variables |
| `env` | Display all environment variables |
| `exit` | Exit the shell with optional status code |
| `history` | Display command history |

---

## Compilation

```bash
# Clone the repository
git clone git@github.com:FumiVZ/minishell.git
cd minishell

# Compile
make

# Clean object files
make clean

# Full clean (including binary)
make fclean

# Recompile
make re
```

### Requirements

- GCC or Clang compiler
- GNU Make
- readline library (`libreadline-dev` on Debian/Ubuntu)

---

## Usage

```bash
# Run minishell
./minishell

# Example commands
minishell$ echo "Hello, World!"
Hello, World!

minishell$ ls -la | grep minishell | wc -l
1

minishell$ cat << EOF > output.txt
> Hello
> World
> EOF

minishell$ export MY_VAR="42 Lyon"
minishell$ echo $MY_VAR
42 Lyon

minishell$ (cd /tmp && pwd) && pwd
/tmp
/home/user

minishell$ exit
```

---

## Project Structure

```
minishell/
├── builtins/          # Built-in command implementations
│   ├── cd/            # Change directory
│   ├── echo/          # Echo command
│   ├── env/           # Environment management
│   ├── exit/          # Exit and cleanup
│   ├── export/        # Export variables
│   ├── history/       # Command history
│   ├── pwd/           # Print working directory
│   └── unset/         # Unset variables
├── code/
│   ├── error/         # Error handling
│   ├── exec/          # Command execution engine
│   ├── header/        # Header files
│   ├── prompt/        # Shell prompt and main loop
│   ├── split_command/ # Command parsing and expansion
│   └── split_line/    # Input tokenization
├── libft/             # Custom C library (42 libft)
└── Makefile
```

---

## Authors

| Author | GitHub |
|--------|--------|
| **vzuccare** | [FumiVZ](https://github.com/FumiVZ) |
| **machrist** | [Denos-soneD](https://github.com/Denos-soneD) |

---

<p align="center">
  Made with ❤️ at <strong>42 Lyon</strong>
</p>
