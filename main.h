#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <limits.h>
#include <signal.h>

#define AND_OP 1
#define OR_OP 2
#define NO_OP 0

/**
* struct variables - Shell's variables
* @av: Command line arguments
* @buffer: Command buffer
* @env: Environment variables
* @count: Commands count
* @argv: Arguments when the shell was opened
* @status: Exit status
* @commands: Double pointer to commands
* @line_num: Line number of the command
* @next_op: Next operator flag
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
int line_num;
int next_op;
} vars_t;

int main(int argc __attribute__((unused)), char **argv, char **environment);
void sigint_handler(int sig);
int _putchar(char c);
int get_last_arg_index(char **args);

void (*find_builtin_command(vars_t *vars))(vars_t *vars);
int execute_path_command(char *command, vars_t *vars);
void check_for_command(vars_t *vars);
int execute_locally(vars_t *vars);
int is_command_in_path(char *str);

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

void perform_exit(vars_t *vars);
void print_env(vars_t *vars);
void add_env_variable(vars_t *vars);
void remove_env_variable(vars_t *vars);
void change_working_directory(vars_t *vars);

void create_env_var(vars_t *vars);
char *create_env_string(char *key, char *value);
char **find_env_var(char **env, char *key);
int _atoi(char *str);

char **make_env(char **env);
void free_env(char **env);
void set_env_var(vars_t *vars, char *key, char *value);

#define TOKENS_INITIAL_CAPACITY 10

char **tokenize(char *buffer, char *delimiter);
char **_realloc(char **ptr, size_t *size);
char *_strtok(char *str, const char *delim);
unsigned int string_match(char c, const char *str);

ssize_t _puts(char *str);
unsigned int _strlen(char *str);
char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strct1, char *strct2);

void print_error(vars_t *vars, char *msg);
void _puts2(char *str);
char *uint_to_ascii(unsigned int count);

#endif
