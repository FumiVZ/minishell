<p align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/minishellm.png" alt="minishell badge" />
</p>

<h1 align="center">Minishell</h1>

<p align="center">
  <b>As beautiful as a shell</b>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/42-Lyon-blue?style=for-the-badge" alt="42 Lyon" />
  <img src="https://img.shields.io/badge/Score-109%2F100-brightgreen?style=for-the-badge" alt="Score" />
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c" alt="C Language" />
</p>

---

## Description

**Minishell** is a 42 School project that challenges students to create their own shell, inspired by bash. This project provides a deep understanding of processes, file descriptors, and the inner workings of Unix shells.

The goal is to implement a functional shell capable of:
- Executing commands with arguments
- Handling environment variables
- Managing redirections and pipes
- Supporting logical operators and subshells

---

## Features

| Category | Feature | Description |
|----------|---------|-------------|
| **Execution** | Command execution | Execute binaries from PATH or absolute/relative paths |
| **Execution** | Pipes `\|` | Chain multiple commands together |
| **Execution** | Logical operators | `&&` and `\|\|` for conditional execution |
| **Execution** | Subshells `()` | Execute commands in a subshell |
| **Redirections** | Input `<` | Redirect input from a file |
| **Redirections** | Output `>` | Redirect output to a file (truncate) |
| **Redirections** | Append `>>` | Redirect output to a file (append) |
| **Redirections** | Heredoc `<<` | Read input until a delimiter is reached |
| **Expansion** | Variables `$VAR` | Expand environment variables |
| **Expansion** | Exit status `$?` | Expand to last command's exit status |
| **Expansion** | Wildcards `*` | Glob pattern matching in current directory |
| **Parsing** | Single quotes `'` | Preserve literal value of characters |
| **Parsing** | Double quotes `"` | Preserve literals, allow `$` expansion |
| **Signals** | Ctrl+C | Display new prompt |
| **Signals** | Ctrl+D | Exit shell |
| **Signals** | Ctrl+\\ | No action (ignored) |

---

## Built-in Commands

| Command | Description |
|---------|-------------|
| `echo` | Display text with `-n` option support |
| `cd` | Change directory (supports `-`, `~`) |
| `pwd` | Print working directory |
| `export` | Set environment variables |
| `unset` | Unset environment variables |
| `env` | Display environment variables |
| `exit` | Exit the shell with optional status |
| `history` | Display command history |

---

## Project Structure

```
minishell/
├── builtins/           # Built-in command implementations
│   ├── cd/             # cd command with PWD/OLDPWD handling
│   ├── echo/           # echo with -n flag support
│   ├── env/            # Environment management
│   ├── exit/           # Exit and cleanup
│   ├── export/         # Variable export
│   ├── history/        # Command history
│   ├── pwd/            # Print working directory
│   └── unset/          # Unset variables
├── code/
│   ├── error/          # Error handling and messages
│   ├── exec/           # Command execution and pipes
│   ├── header/         # Header files
│   ├── prompt/         # Main loop and signal handling
│   ├── split_command/  # Tokenization and expansion
│   └── split_line/     # Input parsing and syntax check
└── libft/              # Custom C library
```

---

## Compilation

### Requirements

- GCC or Clang compiler
- GNU Make
- readline library
- ncurses library

### Build

```bash
# Clone the repository
git clone git@github.com:FumiVZ/minishell.git
cd minishell

# Compile
make

# Clean object files
make clean

# Full clean (objects + executable)
make fclean

# Rebuild
make re
```

---

## Usage

```bash
# Run minishell
./minishell

# Example commands
minishell$ echo "Hello, World!"
Hello, World!

minishell$ ls -la | grep ".c" | wc -l
42

minishell$ cat << EOF > output.txt
> Hello
> World
> EOF

minishell$ export VAR="value" && echo $VAR
value

minishell$ (cd /tmp && pwd) && pwd
/tmp
/home/user

minishell$ exit
```

---

## Authors

| Author | GitHub | 42 Login |
|--------|--------|----------|
| **Vincent Zuccarello** | [@FumiVZ](https://github.com/FumiVZ) | vzuccare |
| **Matéo Christol** | [@Denos-soneD](https://github.com/Denos-soneD) | machrist |

---

<p align="center">
  Made with <img src="https://img.shields.io/badge/C-00599C?style=flat&logo=c&logoColor=white" alt="C" /> at <b>42 Lyon</b>
</p>
