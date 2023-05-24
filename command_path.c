#include "main.h"

/**
* find_builtin - Checks if the command is a builtin
* @vars: Pointer to the struct of shell variables
* Return: Returns a pointer to the function or NULL
*/
void (*find_builtin(vars_t *vars))(vars_t *vars)
{
builtins_t builtins[] = {
{"exit", _exit_shell},
{"env", print_env_vars},
{"setenv", add_env_var},
{"unsetenv", remove_env_var},
{"cd", change_working_directory},
{NULL, NULL}
};
builtins_t *builtin;

for (builtin = builtins; builtin->name != NULL; ++builtin)
{
if (_strcmpr(vars->av[0], builtin->name) == 0)
{
return (builtin->f);
}
}
return (NULL);
}

/**
* check_command - Checks if the command is in the PATH
* @vars: Pointer to the struct of shell variables
* Return: Nothing
*/
void check_command(vars_t *vars)
{
char *path, *path_copy, **path_tokens, *check, **env = environ;
unsigned int i, j = 0;
int command_found = 0;

if (command_is_in_path(vars->av[0]))
j = local_execute(vars);
else
{
while (*env && (_strncmp(*env, "PATH=", 5) || !(path = *env + 5)))
env++;
if (!path)
{
dprintf(STDERR_FILENO, "./hsh: %d: %s: not found\n", vars->ln, vars->av[0]);
vars->status = 127, _exit_shell(vars);
}
path_copy = _strdup(path);
if (!path_copy)
{
perror("Fatal Error");
return;
}
path_tokens = tokenizer(path_copy, ":");
for (i = 0; path_tokens[i]; i++)
{
check = _strcat(path_tokens[i], vars->av[0]);
if (access(check, F_OK) == 0)
{
j = execute_command_in_path(check, vars), free(check);
command_found = 1;
break;
}
free(check);
}
free(path_tokens), free(path_copy);
if (!command_found)
dprintf(STDERR_FILENO, "./hsh: %d: %s: not found\n", vars->ln, vars->av[0]);
vars->status = 127;
}
if (j == 1)
_exit_shell(vars);
}

/**
* execute_command_in_path - Executes a command in the path
* @command: Full path to the command
* @vars: Pointer to the struct of shell variables
* Return: 0 on success, 1 if failed
*/
int execute_command_in_path(char *command, vars_t *vars)
{
pid_t pid = fork();
int status;

if (access(command, X_OK) == -1)
{
perror("Permission denied");
vars->status = 126;
return (1);
}
if (pid == -1)
{
perror(NULL);
vars->status = 2;
return (1);
}
else if (pid == 0)
{
execve(command, vars->av, vars->env);
perror(NULL);
exit(127);
}
else
{
wait(&vars->status);
if (WIFEXITED(status))
{
vars->status = WEXITSTATUS(status);
}
else if (WIFSIGNALED(status))
{
vars->status = 128 + WTERMSIG(status);
if (WTERMSIG(status) == SIGINT)
{
vars->status = 130;
}
}
return (0);
}
}

/**
* local_execute - Executes the command in the current working directory
* @vars: Pointer to the struct of shell variables
* Return: 0 on success, 1 on failure
*/
int local_execute(vars_t *vars)
{
pid_t pid;
struct stat buf;

if (stat(vars->av[0], &buf) == 0)
{
if (access(vars->av[0], X_OK) == 0)
{
pid = fork();
if (pid == -1)
perror(NULL);
if (pid == 0)
{
if (execve(vars->av[0], vars->av, vars->env) == -1)
perror(NULL);
}
else
{
wait(&vars->status);
if (WIFEXITED(vars->status))
vars->status = WEXITSTATUS(vars->status);
else if (WIFSIGNALED(vars->status) && WTERMSIG(vars->status) == SIGINT)
vars->status = 130;
return (0);
}
vars->status = 127;
return (1);
}
else
{
perror(vars->av[0]);
vars->status = 126;
}
return (0);
}
perror(vars->av[0]);
vars->status = 127;
return (0);
}

/**
* command_is_in_path - Checks if the command is part of a path
* @str: The command string
* Return: 1 on success, 0 on failure
*/
int command_is_in_path(char *str)
{
unsigned int i;

for (i = 0; str[i]; i++)
{
if (str[i] == '/')
return (1);
}
return (0);
}
