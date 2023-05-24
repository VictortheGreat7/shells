#include "main.h"

/**
* print_error - Prints error messages to standard error
* @vars: Pointer to the struct of shell variables
* @msg: Message to be printed
* Return: Nothing
*/
void print_error(vars_t *vars, char *msg)
{
char *count;

error_puts(vars->argv[0]);
error_puts(": ");
count = uint_to_ascii(vars->count);
error_puts(count);
free(count);
error_puts(": ");
error_puts(vars->av[0]);
if (msg)
{
error_puts(msg);
}
else
perror("");
}

/**
* error_puts - Prints a string to standard error
* @str: String to be printed
* Return: Nothing
*/
void error_puts(char *str)
{
ssize_t num, len;

num = _strlen(str);
len = write(STDERR_FILENO, str, num);
if (len != num)
{
perror("Fatal Error");
exit(1);
}

}

/**
* uint_to_ascii - Converts an unsigned integer to a string
* @count: Unsigned integer to be converted
* Return: Pointer to the converted string
*/
char *uint_to_ascii(unsigned int count)
{
char *num_str;
unsigned int tmp, digits;

tmp = count;
for (digits = 0; tmp != 0; digits++)
tmp /= 10;
num_str = malloc(sizeof(char) * (digits + 1));
if (num_str == NULL)
{
perror("Fatal Error1");
exit(127);
}
num_str[digits] = '\0';
for (--digits; count; --digits)
{
num_str[digits] = (count % 10) + '0';
count /= 10;
}
return (num_str);
}
