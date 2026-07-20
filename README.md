# Minishell

A 42-style shell project that reimplements core Bash behavior in C.

## Description

`minishell` is a command-line shell written in C. It provides an interactive prompt, parses user input, handles quotes and expansions, supports pipes and redirections, and implements several built-in commands.

The project is still in progress, so some Bash features may be missing or incomplete.

## Features

- Interactive prompt with `readline`
- Command parsing and tokenization
- Quote handling and variable expansion
- Pipes and redirections
- Here-doc support
- Built-in commands:
  - `echo`
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Environment variable management
- Signal handling like Ctrl+C and Ctrl+\

## Work in progress

The following commands are currently being implemented and may not be fully functional yet:

- `alias`
- `type`

This project is still under active development, so some Bash-like behaviors may be missing or incomplete.

## Requirements

- `cc`
- `make`
- `readline` development library
- Unix-like environment

## Build

```bash
make
```

## Notes
- `readline.supp` is a file that suppresses the leaks from `readline` command, if you try `valgrind ./minishell`, you'll see some leaks are suppressed.
