#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

/**
* struct variables - Shell's variables
* @av: Command line arguments
* @buffer: Command buffer
* @env: Environment variables
* @count: Commands count
* @argv: Arguments when the shell was opened
* @status: Exit status
* @commands: Double pointer to commands
* @ln: Line number of the command
*/
typedef struct variables
{
char **av;
char *buffer;
char **env;
size_t count;
char **argv;
int status;
char **commands;
int ln;
} vars_t;

int main(int argc __attribute__((unused)), char **argv, char **environment);
void handle_sigint(int sig);
int _putchar(char c);

extern char **environ;

void (*find_builtin(vars_t *vars))(vars_t *vars);
void check_command(vars_t *vars);
int execute_command_in_path(char *command, vars_t *vars);
int local_execute(vars_t *vars);
int command_is_in_path(char *str);

/**
* struct builtins - Struct for the builtin functions
* @name: Name of builtin command
* @f: Function for corresponding builtin
*/
typedef struct builtins
{
char *name;
void (*f)(vars_t *);
} builtins_t;

void _exit_shell(vars_t *vars);
void print_env_vars(vars_t *vars);
void add_env_var(vars_t *vars);
void remove_env_var(vars_t *vars);
void change_working_directory(vars_t *vars);

void create_environ_var(vars_t *vars);
char *create_environ_string(char *key, char *value);
char **find_environ_var(char **env, char *key);
int _atoi(char *str);
int _strncmp(const char *str1, const char *str2, size_t num);

char **make_environ(char **env);
void free_environ(char **env);
void set_env_var(vars_t *vars, char *key, char *value);

#define TOKENS_INITIAL_CAPACITY 10

char **tokenizer(char *buffer, char *delimiter);
char **_realloc(char **ptr, size_t *size);
char *_strtok(char *str, const char *delim);
unsigned int match_string(char c, const char *str);

ssize_t _puts(char *str);
unsigned int _strlen(char *str);
char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strct1, char *strct2);

void print_error(vars_t *vars, char *msg);
void error_puts(char *str);
char *uint_to_ascii(unsigned int count);

#endif
