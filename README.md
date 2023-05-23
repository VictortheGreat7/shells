# Simple Shell Project

This project is a simple implementation of a shell, written in C. It provides a basic shell interface for users to enter commands, and then executes those commands by creating child processes and using system calls to run them.

## Files

- `shell.c`: Contains the main function for the shell program, as well as several utility functions for handling input and executing commands.
- `main.h`: Header file for the main program, containing function prototypes and definitions of data structures used in the program.

## Functions

- `int main(int argc __attribute__((unused)), char **argv, char **environment)`: This is the main function for the shell program. It initializes variables in a vars_t struct and sets up signal handling for SIGINT. The function then checks if standard input is coming from a pipe and sets is_pipe accordingly. If is_pipe is 0, it prints the shell prompt ($ ) to standard output. The function then enters a loop that reads a line of input from standard input with getline(), tokenizes the line by semicolon and newline characters, and then tokenizes each resulting command by whitespace characters. It then checks if the resulting command is a built-in command with find_builtin_command(), and if so, it calls the corresponding built-in function. If not, it calls check_for_command() to execute the command. The function then frees memory allocated for the vars_t struct and exits with the exit status stored in vars.status.

- `void sigint_handler(int sig)`: This function handles the SIGINT signal sent to the process. It first ignores the signal parameter sig, then prints a newline character and the shell prompt ($ ) to standard output, and finally flushes standard output.

- `int _putchar(char c)`: Writes a character to standard output.


- `void (*find_builtin_command(vars_t *vars))(vars_t *vars)`: This function checks if the command specified in vars->av[0] is a built-in command. It loops through an array of builtins_t structures and compares the command name with vars->av[0]. If a match is found, it returns a pointer to the corresponding function. Otherwise, it returns NULL.

- `void check_for_command(vars_t *vars)`: This function checks if the command specified in vars->av[0] is in the PATH environment variable. If it is, it executes it with execute_locally(). Otherwise, it loops through each directory in the PATH and checks if the command exists in that directory with execute_path_command(). If the command is not found in any directory, it prints an error message and sets the exit status to 127.

- `int execute_path_command(char *command, vars_t *vars)`: This function executes a command specified by a full path. It first checks if the user has permission to execute the command. If not, it prints an error message and returns 1. It then forks a new process and executes the command with the arguments and environment variables passed in vars. If an error occurs, it prints an error message and exits with status code 127. Otherwise, it waits for the child process to finish and sets the exit status to the child process's exit status.

- `int execute_locally(vars_t *vars)`: This function executes the command in the current working directory. It first checks if the file exists and is executable. If not, it prints an error message and returns 1. It then forks a new process and executes the command with the arguments and environment variables passed in vars. If an error occurs, it prints an error message and sets the exit status to 127. Otherwise, it waits for the childprocess to finish and sets the exit status to the child process's exit status.

- `int is_command_in_path(char *str)`: This function checks if the command string str contains a forward slash /, indicating that the command is specified by a full path. If it does, it returns 1. Otherwise, it returns 0.


- `void perform_exit(vars_t *vars))`: This function exits the shell program. It first checks if the user entered exit as the command. If there is an additional argument, it converts it to an integer and sets it as the exit status. If the argument cannot be converted to an integer, it sets the exit status to 2 and prints an error message. It then frees all allocated memory and exits the program with the specified exit status.

- `void print_env(vars_t *vars)`: This function prints the current environment variables. It loops through vars->env and writes each variable to standard output with a newline character.

- `void add_env_variable(vars_t *vars)`: This function creates a new environment variable or edits an existing one. It first checks if the user entered the correct number of arguments. If the first argument is not an existing environment variable, it creates a new one. Otherwise, it updates the existing one with the new value.

- `void remove_env_variable(vars_t *vars)`: This function removes an environment variable. It first checks if the user entered the correct number of arguments. If the argument is not an existing environment variable, it prints an error message. Otherwise, it creates a new new_env array without the variable to be removed and sets it as the new environment variable. It then frees the memory allocated for the removed variable.

- `void change_working_directory(vars_t *vars)`: This function changes the current working directory. If there is no argument provided, it attempts to change the directory to the home directory. If - is provided as the argument, it changes to the previous working directory. Otherwise, it changes to the directory specified by the argument. It then sets the PWD and OLDPWD environment variables to the new and old working directories, respectively. If an error occurs, it prints an error message.


- `void create_env_var(vars_t *vars)`: This function creates a new environment variable with the name and value specified in vars->av[1] and vars->av[2], respectively. It first counts the number of environment variables in vars->env. It then allocates memory for a new array of strings new_env with size i+2, where i is the number of environment variables. It then copies each environment variable into the new array with a for loop and uses create_env_string() to create a new string for the new environment variable. If an error occurs during memory allocation or string creation, it prints an error message and sets the exit status to 127. Finally, it adds a NULL terminator to the end of the new array and frees the memory allocated for the old environment array before setting vars->env to the new array.

- `char *create_env_string(char *key, char *value)`: This function creates a new environment variable string by concatenating key, '=', and value into a single string. It first determines the length of key and value, allocates memory for a new string with length len1 + len2 + 2 (for the '=' character and null terminator), and copies key, '=', and value into the new string using a for loop. Finally, it returns a pointerto the resulting string. If an error occurs during memory allocation, it returns NULL.

- `char **find_env_var(char **env, char *key)`: This function searches the array of environment variables env for an environment variable with the name key. It first determines the length of key and then iterates through env with a for loop, comparing each environment variable to key. If a match is found, it returns a pointer to the address of the environment variable. If no match is found, it returns NULL

- `int _atoi(char *str)`: This function converts a string str into an integer and returns the resulting integer. It first determines the maximum number of digits an integer can have on the current system and stores it in digits. It then iterates through the string with a for loop, multiplying num by 10 and adding the value of the current digit until the end of the string or digits is reached. If a non-digit character is encountered, it returns -1. If the resulting integer overflows or underflows, it returns -1. Finally, it returns the resulting integer.

- `int _strncmp(const char *str1, const char *str2, size_t num)`: This function compares the first num characters of two strings str1 and str2. It returns an integer indicating their relative order, with a negative value if str1 is less than str2, a positive value if str1 is greater than str2, and 0 if they are equal up to num characters.


- char **make_env(char **env)`: This function creates a new environment for the shell based on the environment variables passed into it. It first counts the number of environment variables in env. It then allocates memory for a new array of strings new_env with size i+1, where i is the number of environment variables. It then copies each environment variable into the new array with _strdup(). Finally, it adds a NULL terminator to the end of the new array and returns a pointer to it.

- `void free_env(char **env)`: This function frees the memory allocated for the shell's environment by iterating through each element of the array and freeing the memory for the string and then freeing the array itself.

- `void set_env_var(vars_t *vars, char *key, char *value)`: This function sets the value of an environment variable. It first checks if the environment variable already exists by calling find_env_var() with the key. If it exists, it frees the old value and creates a new environment string with create_env_string(). If an error occurs, it prints an error message and sets the exit status to 127. If the environment variable does not exist, it calls create_env_var() to create it and sets the value with create_env_string(). If an error occurs, it prints an error message and sets the exit status to 127.


- `char **tokenize(char *buffer, char *delimiter)`: This function tokenizes a string buffer with a given delimiter by allocating memory for an array of pointers to tokens, then using _strtok() to extract tokens from the string and store them in the array. If the array is filled, it reallocates more memory. It then returns a pointer to the array of pointers to tokens. If an error occurs during memory allocation, it returns NULL.

- `char **_realloc(char **ptr, size_t *size)`: This function reallocates memory for an array of pointers ptr to resize it, increasing its size by 10 elements each time it is called. It first allocates memory for a new array of pointers new_array, copies the elements of ptr to new_array with a for loop, then frees the memory allocated for ptr. It then returns a pointer to the new array of pointers. If an error occurs during memory allocation, it frees the memory allocated for ptr and returns NULL.

- `char *_strtok(char *str, const char *delim)`: This function is a custom implementation of strtok(). It extracts the next token from a string str using a delimiter delim, and returns a pointer to the token. It uses static variables token_start and current_position to keep track of the start and end of the current tokenin the string. It first sets current_position to the start of the string str, then looks for the first character that is not a delimiter or a comment character (#). It sets token_start to this position, and then looks for the next delimiter or comment character. It then sets this character to a null terminator (\0) and returns a pointer to token_start. If there is no more tokens, it returns NULL.

- `unsigned int string_match(char c, const char *str)`: This function checks if a character c matches any character in a string str. It iterates through the string with a for loop and returns 1 if the character is found, otherwise 0.


- `ssize_t _puts(char *str)`: This function writes a string str to standard output using the write() system call. It first determines the length of the string using _strlen(), writes the string to standard output with write(), and returns the number of characters printed. If an error occurs during writing, it prints a "Fatal Error" message using perror() and returns -1.

- `unsigned int _strlen(char *str)`: This function returns the length of a string str. It iterates through the string with a for loop and increments a length counter until it reaches the null terminator. It then returns the length of the string.

- `char *_strdup(char *strtodup)`: This function duplicates a string strtodup by first determining its length with _strlen(), allocating memory for a new string with malloc(), and then copying each character of strtodup to the new string with a for loop. It then returns a pointer to the new string. If an error occurs during memory allocation, it returns NULL.

- `int _strcmpr(char *strcmp1, char *strcmp2)`: This function compares two strings strcmp1 and strcmp2 by iterating through the strings with a while loop and comparing each character until a difference is found or the end of the string is reached. If the strings are equal, it returns 0. Otherwise, it returns the ASCII difference between the first differing characters.

- char *_strcat(char *strct1, char *strct2)`: This function concatenates two strings strct1 and strct2 into a new string, separated by a forward slash (/). It first determines the lengths of strct1 and strct2 with _strlen(), allocates memory for a new string with malloc(), and then copies each character of strct1 and strct2 to the new string with for loops. It then adds a forward slash character to the new string and sets a null terminator. Finally, it returns a pointer to the new string. If an error occurs during memory allocation, it returns NULL.


- `void print_error(vars_t *vars, char *msg)`: This function prints an error message to standard error. It first prints the name of the shell executable and a colon, followed by the line number and a colon, and finally the command that caused the error. If an additional message msg is provided, it is also printed.

- `void _puts2(char *str)`: This function prints a string to standard error.

- `char *uint_to_ascii(unsigned int count)`: This function converts an unsigned integer count to a string and returns a pointer to the resulting string. It first determines the number of digits in the integer and allocates memory for a string large enough to hold the integer as a string. It then converts the integer to a string one digit at a time, starting with the least significant digit and moving to the most significant digit. Finally, it returns a pointer to the resulting string. If an error occurs during memory allocation, it prints an error message and sets the exit status to 127.

## Compilation

To compile the program, run the following command in the terminal:

```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

This will compile all C files in the current directory into an executable file named `hsh`.

## Usage

To run the shell program, simply run the `hsh` executable file in the terminal. This will open the shell prompt (`$ `), where you can enter commands to execute. The shell supports several built-in commands (`exit`, `env`, `setenv`, `unsetenv`, `cd`) as well as commands in the PATH environment variable(`ls`, `echo`, `pwd`, and others). Enter `exit` to exit the shell program.
