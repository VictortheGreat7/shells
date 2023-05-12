#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
*/
typedef struct variables
{
char **av;
char *buffer;
char **env;
size_t count;
char **argv;
int status;
int readfd;
char **commands;
int line_num;
} vars_t;

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

char **make_env(char **env);
void free_env(char **env);
void command_exit(char *c);

int _putchar(char c);
ssize_t _puts(char *str);
char *_strdup(char *strtodup);
int _strcmpr(char *strcmp1, char *strcmp2);
char *_strcat(char *strct1, char *strct2);
unsigned int _strlen(char *str);

#define TOKENS_INITIAL_CAPACITY 10

char **tokenize(char *buffer, char *delimiter);
char **_realloc(char **ptr, size_t *size);
char *_strtok(char *str, const char *delim);
unsigned int string_match(char c, const char *str);

void (*find_builtin_command(vars_t *vars))(vars_t *vars);
void perform_exit(vars_t *vars);
void print_env(vars_t *vars);
void add_env_variable(vars_t *vars);
void remove_env_variable(vars_t *vars);

void create_env_var(vars_t *vars);
char **find_env_var(char **env, char *key);
char *create_env_string(char *key, char *value);
int _atoi(char *str);

void check_for_command(vars_t *vars);
int execute_path_command(char *command, vars_t *vars);
char *get_path(char **env);
int execute_locally(vars_t *vars);
int is_command_in_path(char *str);

void print_error(vars_t *vars, char *msg);
void _puts2(char *str);
char *uint_to_ascii(unsigned int count);

void sigint_handler(int sig);
int check_interactive(vars_t *vars);

#endif
