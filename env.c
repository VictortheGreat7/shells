#include "main.h"

/**
* make_env - Makes a shell environment from the environment passed into main
* @env: The environment passed into main
* Return: Pointer to the new environment
*/
char **make_env(char **env)
{
char **new_env = NULL;
size_t i;

for (i = 0; env[i] != NULL; i++)
;
new_env = malloc(sizeof(char *) * (i + 1));
if (new_env == NULL)
{
perror("Fatal Error");
exit(1);
}
for (i = 0; env[i] != NULL; i++)
new_env[i] = _strdup(env[i]);
new_env[i] = NULL;
return (new_env);
}

/**
* free_env - Frees the shell's environment
* @env: The shell's environment
* Return: Nothing
*/
void free_env(char **env)
{
unsigned int i;

for (i = 0; env[i] != NULL; i++)
free(env[i]);
free(env);
}

/**
* set_env_var - Sets the value of an environment variable
* @vars: Pointer to the struct of shell variables
* @key: Name of the environment variable
* @value: Value of the environment variable
*/
void set_env_var(vars_t *vars, char *key, char *value)
{
char **env_var = find_env_var(vars->env, key);
char **new_env_var = find_env_var(vars->env, key);
if (env_var != NULL)
{
free(*env_var);
*env_var = create_env_string(key, value);
if (*env_var == NULL)
{
perror("Error");
vars->status = 127;
perform_exit(vars);
}
}
else
{
create_env_var(vars);
*new_env_var = create_env_string(key, value);
if (*new_env_var == NULL)
{
perror("Error");
vars->status = 127;
perform_exit(vars);
}
}
}
