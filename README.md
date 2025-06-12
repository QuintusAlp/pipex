# Pipex

A C program that simulates the behavior of shell pipes, recreating the functionality of bash commands with support for multiple pipes and here_doc:

**Basic usage:**
```bash
< file1 cmd1 | cmd2 > file2
```

**Multiple pipes (bonus):**
```bash
< file1 cmd1 | cmd2 | cmd3 | ... | cmdN > file2
```

**Here_doc (bonus):**
```bash
cmd1 << LIMITER | cmd2 >> file2
```

## 📋 Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Implementation Details](#implementation-details)
- [Testing](#testing)
- [Technical Skills Demonstrated](#technical-skills-demonstrated)

## 🔍 About

Pipex is a 42 School project that challenges students to understand and implement inter-process communication using pipes. The program takes four parameters and executes two commands in sequence, with the output of the first command serving as input to the second command, mimicking shell pipe behavior.

**Equivalent shell commands:**
```bash
# Basic pipex
./pipex file1 cmd1 cmd2 file2
# Same as: < file1 cmd1 | cmd2 > file2

# Multiple pipes (bonus)
./pipex file1 cmd1 cmd2 cmd3 cmd4 file2
# Same as: < file1 cmd1 | cmd2 | cmd3 | cmd4 > file2

# Here_doc (bonus)
./pipex here_doc LIMITER cmd1 cmd2 file2
# Same as: cmd1 << LIMITER | cmd2 >> file2
```

## ✨ Features

- **Process Management**: Creates multiple child processes using `fork()`
- **Inter-Process Communication**: Implements multiple pipes for data transfer between processes
- **File I/O Operations**: Handles input/output file operations
- **Command Execution**: Executes unlimited system commands using `execve()`
- **Here_doc Implementation**: Supports heredoc functionality with custom limiters
- **Multiple Pipes**: Handles unlimited number of commands in pipeline
- **Error Handling**: Comprehensive error management for all edge cases
- **Memory Management**: Proper allocation and deallocation of resources

## 🚀 Installation

1. Clone the repository:
```bash
git clone [your-repo-url]
cd pipex
```

2. Compile the project:
```bash
make
```

3. Clean object files (optional):
```bash
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Recompile everything
```

## 💻 Usage

### Basic Usage
```bash
# Standard pipex (2 commands)
./pipex infile "command1" "command2" outfile

# Multiple pipes (unlimited commands)
./pipex infile "cmd1" "cmd2" "cmd3" "cmd4" ... "cmdN" outfile

# Here_doc usage
./pipex here_doc LIMITER "command1" "command2" outfile
```

## 🔧 Implementation Details

### System Calls Used

- `pipe()`: Creates pipe for inter-process communication
- `fork()`: Creates child processes
- `execve()`: Executes commands
- `dup2()`: Redirects file descriptors
- `open()`: Opens files for reading/writing
- `close()`: Closes file descriptors
- `wait()`/`waitpid()`: Waits for child process completion

### Process Flow

**Basic Pipeline:**
1. **Validation**: Check command-line arguments
2. **Pipe Creation**: Create pipes for communication
3. **Fork Processes**: Create child processes for each command
4. **Execute Commands**: Each process executes its command with proper I/O redirection

**Multiple Pipes (Bonus):**
1. **Dynamic Pipe Array**: Create array of pipes based on number of commands
2. **Process Chain**: Fork processes for each command in the pipeline
3. **I/O Redirection**: Connect each process's output to the next process's input
4. **Resource Management**: Properly close unused file descriptors
5. **Wait for Completion**: Parent waits for all child processes

**Here_doc (Bonus):**
1. **Limiter Detection**: Check for "here_doc" as first argument
2. **Input Reading**: Read from stdin until limiter is found
3. **Temporary Pipe**: Use pipe as temporary storage for here_doc content
4. **Pipeline Execution**: Execute commands with here_doc input

## 🧪 Testing

### Test Cases

**Basic Functionality:**
1. **Standard pipes**: Two command pipeline
2. **Multiple pipes**: Three or more commands in pipeline
3. **Here_doc**: Heredoc with various limiters

**Error Handling:**
1. **Invalid files**: Non-existent input files, permission issues
2. **Invalid commands**: Non-existent commands, malformed commands
3. **Edge cases**: Empty files, binary files, large files
4. **Memory leaks**: Valgrind testing for memory management
5. **Process management**: Proper cleanup of child processes

### Example Test Scripts

**Basic testing:**
```bash
# Test standard functionality
./pipex input.txt "cat" "wc -l" output.txt

# Test multiple pipes
./pipex input.txt "cat" "grep hello" "sort" "uniq" output.txt

# Test here_doc
echo -e "hello world\ntest line\nEOF" | ./pipex here_doc EOF "grep hello" "wc -w" output.txt
```

**Stress testing:**
```bash
# Test with many commands
./pipex large_file.txt "cat" "sort" "uniq" "wc -l" "cat" "head -10" result.txt

# Test error handling
./pipex nonexistent.txt "cat" "wc -l" output.txt
./pipex input.txt "invalidcmd" "wc -l" output.txt
```

## 🛠️ Technical Skills Demonstrated

- **Advanced System Programming**: Complex process management with multiple pipes and process synchronization
- **C Programming**: Advanced C concepts including dynamic memory allocation, pointer manipulation, and complex data structures
- **Inter-Process Communication**: Implementation of multiple pipes and process coordination
- **Here_doc Implementation**: Custom implementation of shell heredoc functionality
- **Dynamic Resource Management**: Handling variable number of processes and pipes
- **Error Handling**: Robust error checking across multiple processes and system calls
- **Code Organization**: Clean, modular code structure handling complex logic
- **Memory Management**: Advanced memory management with dynamic allocation for variable-sized pipelines
- **Process Synchronization**: Proper coordination of multiple child processes
- **File Descriptor Management**: Complex I/O redirection across multiple processes
- **Algorithm Design**: Efficient pipeline execution with optimal resource usage

## 📝 Notes

- This project is part of the 42 School curriculum (includes bonus part)
- **Bonus features implemented:**
  - Multiple pipes (unlimited number of commands)
  - Here_doc functionality with custom limiters
- Developed following 42's strict coding standards (Norminette)
- All functions are limited to 25 lines as per 42 standards
- No global variables used
- Proper error handling for all system calls
- Dynamic memory allocation for variable pipeline sizes
- Comprehensive process and file descriptor management
