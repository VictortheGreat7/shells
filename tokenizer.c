#include "main.h"

/**
* tokenizer - Tokenizes a buffer with a delimiter
* @buffer: Buffer to be tokenized
* @delimiter: Delimiter to be tokenized with
* Return: Pointer to an array of pointers to tokens
*/
char **tokenizer(char *buffer, char *delimiter)
{
char **tokens = NULL;
size_t i = 0, mcount = TOKENS_INITIAL_CAPACITY;

if (buffer == NULL)
return (NULL);

tokens = malloc(sizeof(char *) * mcount);
if (tokens == NULL)
{
perror("Fatal Error");
return (NULL);
}

while ((tokens[i] = _strtok(buffer, delimiter)) != NULL)
{
i++;
if (i == mcount)
{
tokens = _realloc(tokens, &mcount);
if (tokens == NULL)
{
perror("Fatal Error");
return (NULL);
}
}
buffer = NULL;
}

return (tokens);
}

/**
* _realloc - Reallocates a memory block to resize it
* @ptr: Pointer to the old array
* @size: Pointer to number of elements in the old array
* Return: Pointer to the new array
*/
char **_realloc(char **ptr, size_t *size)
{
char **new_array;
size_t i;

new_array = malloc(sizeof(char *) * ((*size) + 10));
if (new_array == NULL)
{
free(ptr);
return (NULL);
}

for (i = 0; i < (*size); i++)
{
new_array[i] = ptr[i];
}

*size += 10;
free(ptr);
return (new_array);
}

/**
* _strtok - Custom strtok
* @str: String to be tokenized
* @delim: Delimiter to be tokenized against
* Return: Pointer to the next token or NULL
*/
char *_strtok(char *str, const char *delim)
{
static char *token_start;
static char *current_position;
unsigned int i;

if (str != NULL)
current_position = str;
token_start = current_position;
if (token_start == NULL)
return (NULL);
for (i = 0; current_position[i] != '\0'; i++)
{
if (match_string(current_position[i], delim) == 0)
break;
}

if (current_position[i] == '\0' || current_position[i] == '#')
{
current_position = NULL;
return (NULL);
}
token_start = current_position + i;
current_position = token_start;
for (i = 0; current_position[i] != '\0'; i++)
{
if (match_string(current_position[i], delim) == 1)
break;
}

if (current_position[i] == '\0')
current_position = NULL;
else
{
current_position[i] = '\0';
current_position = current_position + i + 1;
if (*current_position == '\0')
current_position = NULL;
}
return (token_start);
}

/**
* match_string - Checks if a character matches any in a string
* @c: Character to be checked
* @str: String to be checked
* Return: 1 if it matches, 0 if it does not
*/
unsigned int match_string(char c, const char *str)
{
unsigned int i;

for (i = 0; str[i] != '\0'; i++)
{
if (c == str[i])
return (1);
}
return (0);
}
