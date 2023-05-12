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
