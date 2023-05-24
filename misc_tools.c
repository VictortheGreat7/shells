#include "main.h"

/**
* create_environ_var - Create a new environment variable
* @vars: Pointer to the struct of shell variables
* Return: Nothing
*/
void create_environ_var(vars_t *vars)
{
unsigned int i;
char **new_env;

for (i = 0; vars->env[i] != NULL; i++)
;
new_env = malloc(sizeof(char *) * (i + 2));
if (new_env == NULL)
{
perror("Error");
vars->status = 127;
_exit_shell(vars);
}
for (i = 0; vars->env[i] != NULL; i++)
new_env[i] = vars->env[i];
new_env[i] = create_environ_string(vars->av[1], vars->av[2]);
if (new_env[i] == NULL)
{
perror("Error");
free(vars->buffer);
free(vars->commands);
free(vars->av);
free_environ(vars->env);
free(new_env);
exit(127);
}
new_env[i + 1] = NULL;
free(vars->env);
vars->env = new_env;
}

/**
* create_environ_string - Create a new environment variable string
* @key: Name of the environment variable
* @value: Value of the environment variable
* Return: Pointer to the new string;
*/
char *create_environ_string(char *key, char *value)
{
unsigned int len1, len2, i, j;
char *new_env_string;

len1 = _strlen(key);
len2 = _strlen(value);
new_env_string = malloc(sizeof(char) * (len1 + len2 + 2));
if (new_env_string == NULL)
return (NULL);
for (i = 0; key[i] != '\0'; i++)
new_env_string[i] = key[i];
new_env_string[i] = '=';
for (j = 0; value[j] != '\0'; j++)
new_env_string[i + 1 + j] = value[j];
new_env_string[i + 1 + j] = '\0';
return (new_env_string);
}

/**
* find_environ_var - Finds an environment variable
* @env: Array of environment variables
* @key: Environment variable to find
* Return: Pointer to address of the environment variable
*/
char **find_environ_var(char **env, char *key)
{
unsigned int i, j, len;

len = _strlen(key);
for (i = 0; env[i] != NULL; i++)
{
for (j = 0; j < len; j++)
if (key[j] != env[i][j])
break;
if (j == len && env[i][j] == '=')
return (&env[i]);
}
return (NULL);
}

/**
* _atoi - Converts a string into an integer
* @str: String to be converted
* Return: The integer value, or -1 if an error occurs
*/
int _atoi(char *str)
{
unsigned int i, digits;
int num = 0, num_test;

num_test = INT_MAX;
for (digits = 0; num_test != 0; digits++)
num_test /= 10;
for (i = 0; str[i] != '\0' && i < digits; i++)
{
num *= 10;
if (str[i] < '0' || str[i] > '9')
return (-1);
if ((i == digits - 1) && (str[i] - '0' > INT_MAX % 10))
return (-1);
num += str[i] - '0';
if ((i == digits - 2) && (str[i + 1] != '\0') && (num > INT_MAX / 10))
return (-1);
}
if (i > digits)
return (-1);
return (num);
}

/**
* _strncmp - Compares a maximum of num bytes of two strings
* @str1: First string to be compared
* @str2: Second string to be compared
* @num: The maximum number of bytes to compare
* Return: 0 if sucessful, a negative value or a positive value if failed
*/
int _strncmp(const char *str1, const char *str2, size_t num)
{
size_t i;

for (i = 0; i < num; i++)
{
if (str1[i] != str2[i])
return (str1[i] - str2[i]);
else if (str1[i] == '\0')
return (0);
}
return (0);
}
