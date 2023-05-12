#include "main.h"

/**
* check_interactive - Checks if shell is interactive
* @vars: Pointer to the vars_t struct
* Return: 1 if successful, 0 if failed
*/
int check_interactive(vars_t *vars)
{
return (isatty(STDIN_FILENO) && vars->readfd <= 2);
}
