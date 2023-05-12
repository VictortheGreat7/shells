#include "main.h"

/**
* execute_path_command - Executes a command in the path
* @command: Full path to the command
* @vars: Pointer to the struct of shell variables
* Return: 0 on success, 1 if failed
*/
int execute_path_command(char *command, vars_t *vars)
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
* execute_locally - Executes the command in the current working directory
* @vars: Pointer to the struct of shell variables
* Return: 0 on success, 1 on failure
*/
int execute_locally(vars_t *vars)
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
* check_for_command - Checks if the command is in the PATH
* @vars: Pointer to the struct of shell variables
* Return: Nothing
*/
void check_for_command(vars_t *vars)
{
char *path, *check;
unsigned int i, j = 0;
char **path_tokens;
struct stat buf;

if (is_command_in_path(vars->av[0]))
j = execute_locally(vars);
else
{
path = getenv("PATH");
if (!path)
{
dprintf(STDERR_FILENO, "./hsh: %d: %s: not found\n",
vars->line_num, vars->av[0]);
vars->status = 127;
perform_exit(vars);
}
path_tokens = tokenize(path + 5, ":");
for (i = 0; path_tokens[i]; i++)
{
check = _strcat(path_tokens[i], vars->av[0]);
if (stat(check, &buf) == 0)
{
j = execute_path_command(check, vars);
free(check);
break;
}
free(check);
}
free(path_tokens);
if (!path_tokens[i])
{
dprintf(STDERR_FILENO, "./hsh: %d: %s: not found\n",
vars->line_num, vars->av[0]);
vars->status = 127;
}
}
if (j == 1)
perform_exit(vars);
}

/**
* is_command_in_path - Checks if the command is part of a path
* @str: The command string
* Return: 1 on success, 0 on failure
*/
int is_command_in_path(char *str)
{
unsigned int i;

for (i = 0; str[i]; i++)
{
if (str[i] == '/')
return (1);
}
return (0);
}