#include "main.h"

/**
* _putchar - Writes the character c to stdout
* @c: The character to print
*
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int _putchar(char c)
{
return (write(1, &c, 1));
}

/**
* sigint_handler - Handles the SIGINT signal sent to the process
* @sig: The signal number
* Return: Nothing
*/

void sigint_handler(int sig)
{
(void)sig;
_putchar('\n');
write(STDOUT_FILENO, "$ ", 2);
fflush(stdout);
}

int get_last_arg_index(char **args)
{
int i;
for(i = 0; args[i] != NULL; i++);
return (i - 1);
}

/**
* main - Main function for the simple shell program
* @argc: Number of arguments passed to main
* @argv: Array of arguments passed to main
* @environment: Array of environment variables
* Return: 0 or exit status, or unknown
*/
int main(int argc __attribute__((unused)), char **argv, char **environment)
{
size_t len_buffer = 0;
unsigned int is_pipe = 0, i;
vars_t vars = {NULL, NULL, NULL, 0, NULL, 0, NULL, 1, NO_OP};
vars.av = (char **) malloc(sizeof(char *));
vars.av[0] = NULL;
vars.argv = argv;
vars.env = make_env(environment);

signal(SIGINT, sigint_handler);
if (!isatty(STDIN_FILENO))
is_pipe = 1;
if (is_pipe == 0)
_puts("$ ");
fflush(stdout);
while (getline(&(vars.buffer), &len_buffer, stdin) != -1)
{
vars.count++;
vars.commands = tokenize(vars.buffer, ";");
for (i = 0; vars.commands && vars.commands[i] != NULL; i++)
{
vars.av = tokenize(vars.commands[i], "\n \t\r");
if (vars.av && vars.av[0])
{
int last_arg_index = get_last_arg_index(vars.av);
if (last_arg_index != -1 && (_strcmpr(vars.av[last_arg_index], "&&") == 0 || _strcmpr(vars.av[last_arg_index], "||") == 0))
{
vars.next_op = _strcmpr(vars.av[last_arg_index], "&&") == 0 ? AND_OP : OR_OP;
vars.av[last_arg_index] = NULL;
}
else
{
vars.next_op = NO_OP;
}

void (*builtin_func)(vars_t *) = find_builtin_command(&vars);
builtin_func != NULL ? builtin_func(&vars) : check_for_command(&vars);
}
free(vars.av);
}
free(vars.buffer);
free(vars.commands);
vars.buffer = NULL;
if (is_pipe == 0)
_puts("$ ");
fflush(stdout);
}
if (is_pipe == 0)
_puts("\n");
free_env(vars.env);
free(vars.buffer);
exit(vars.status);
}
