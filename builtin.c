#include "main.h"

/**
* _exit_shell - Exits the shell
* @vars: Pointer to the struct of shell variables
* Return: Nothing
*/
void _exit_shell(vars_t *vars)
{
int exit_status;

if (_strcmpr(vars->av[0], "exit") == 0 && vars->av[1] != NULL)
{
exit_status = _atoi(vars->av[1]);
if (exit_status == -1)
{
vars->status = 2;
print_error(vars, ": Invalid number format: ");
error_puts(vars->av[1]);
error_puts("\n");
return;
}
vars->status = exit_status;
}
else
{
vars->status = 0;
}
free(vars->buffer);
free(vars->av);
free(vars->commands);
free_environ(vars->env);
exit(vars->status);
}

/**
* print_env_vars - Prints the current environment
* @vars: Pointer to the struct of shell variables
* Return: Nothing
*/
void print_env_vars(vars_t *vars)
{
unsigned int i;

for (i = 0; vars->env[i]; i++)
{
_puts(vars->env[i]);
_puts("\n");
}
vars->status = 0;
}

/**
* add_env_var - Creates an environment variable or edits an existing one
* @vars: Pointer to the struct of shell variables
* Return: Nothing
*/
void add_env_var(vars_t *vars)
{
char **existing_var;
char *new_value;

if (vars->av[1] == NULL || vars->av[2] == NULL)
{
print_error(vars, ": Invalid number of arguments\n");
vars->status = 2;
return;
}

existing_var = find_environ_var(vars->env, vars->av[1]);
if (existing_var == NULL)
create_environ_var(vars);
else
{
new_value = create_environ_string(vars->av[1], vars->av[2]);
if (new_value == NULL)
{
perror("Error");
free(vars->buffer);
free(vars->commands);
free(vars->av);
free_environ(vars->env);
exit(127);
}
free(*existing_var);
*existing_var = new_value;
}
vars->status = 0;
}

/**
* remove_env_var - Remove an environment variable
* @vars: Pointer to the struct of shell variables
* Return: Nothing
*/
void remove_env_var(vars_t *vars)
{
char **existing_var, **new_env;
unsigned int i, j;

if (vars->av[1] == NULL)
{
print_error(vars, ": Invalid number of arguments\n");
vars->status = 2;
return;
}

existing_var = find_environ_var(vars->env, vars->av[1]);
if (existing_var == NULL)
{
print_error(vars, ": There is no variable to remove");
return;
}

for (i = 0; vars->env[i] != NULL; i++)
;

new_env = malloc(sizeof(char *) * i);
if (new_env == NULL)
{
perror("Error");
vars->status = 127;
_exit_shell(vars);
}

for (i = 0; vars->env[i] != *existing_var; i++)
new_env[i] = vars->env[i];

for (j = i + 1; vars->env[j] != NULL; j++, i++)
new_env[i] = vars->env[j];

new_env[i] = NULL;
free(*existing_var);
free(vars->env);
vars->env = new_env;
vars->status = 0;
}

/**
 * change_working_directory - Changes the current working directory
 * @vars: Pointer to the struct of shell variables
 * Return: Nothing
 */
void change_working_directory(vars_t *vars)
{
char *desired_dir;
char *current_working_dir;
char *previous_working_dir;

if (vars->av[1] == NULL)
{
char **home_dir_ptr = find_environ_var(vars->env, "HOME");
char *home_dir = home_dir_ptr != NULL ? (*home_dir_ptr) + _strlen("HOME=") :
NULL;
desired_dir = home_dir != NULL ? home_dir :
(print_error(vars, ": No home directory found\n"), NULL);
}
else if (_strcmpr(vars->av[1], "-") == 0)
{
char **env_var = find_environ_var(vars->env, "OLDPWD");
char *old_dir = env_var != NULL ? (*env_var) + _strlen("OLDPWD=") : NULL;
desired_dir = old_dir != NULL ? old_dir :
(print_error(vars, ": OLDPWD not set\n"), NULL);
}
else
{
desired_dir = vars->av[1];
}

if (chdir(desired_dir) != 0)
{
print_error(vars, ": No such file or directory\n");
return;
}

previous_working_dir = find_environ_var(vars->env, "PWD")[0];
set_env_var(vars, "OLDPWD", previous_working_dir + _strlen("PWD="));
current_working_dir = getcwd(NULL, 0);
set_env_var(vars, "PWD", current_working_dir);
free(current_working_dir);

vars->status = 0;
}
