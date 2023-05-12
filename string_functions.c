#include "main.h"

/**
* _puts - Writes a string to standard output
* @str: String to be written
* Return: Number of chars printed or -1, if failed
*/
ssize_t _puts(char *str)
{
ssize_t num = _strlen(str);
ssize_t len = write(STDOUT_FILENO, str, num);

if (len != num)
{
perror("Fatal Error");
return (-1);
}
return (len);
}

/**
* _strlen - Returns the length of a string
* @str: String to be measured
* Return: Returns the length of string
*/
unsigned int _strlen(char *str)
{
unsigned int len;

for (len = 0; str[len]; len++)
;
return (len);
}

/**
* _strdup - Duplicates a string
* @strtodup: String to be duplicated
* Return: Returns a pointer to the newly duplicated string
*/
char *_strdup(char *strtodup)
{
char *copy;
int len, i;

if (strtodup == 0)
return (NULL);

for (len = 0; strtodup[len]; len++)
;
copy = malloc((len + 1) * sizeof(char));

for (i = 0; i <= len; i++)
copy[i] = strtodup[i];

return (copy);
}

/**
* _strcmpr - Compares two strings
* @strcmp1: First string, of two, to be compared
* @strcmp2: Second string, of two, to be compared
* Return: 0 on success or the ASCII diff of the differing chars, if failed
*/
int _strcmpr(char *strcmp1, char *strcmp2)
{
int i = 0;

while (strcmp1[i] == strcmp2[i])
{
if (strcmp1[i] == '\0')
return (0);
i++;
}

return (strcmp1[i] - strcmp2[i]);
}

/**
* _strcat - Concatenates two strings
* @strct1: First string
* @strct2: Second string
* Return: Returns a pointer to the concatenated string
*/
char *_strcat(char *strct1, char *strct2)
{
char *new_string;
unsigned int len1, len2, new_len, i, j;

len1 = 0;
len2 = 0;

if (strct1 == NULL)
len1 = 0;
else
{
for (len1 = 0; strct1[len1]; len1++)
;
}

if (strct2 == NULL)
len2 = 0;
else
{
for (len2 = 0; strct2[len2]; len2++)
;
}

new_len = len1 + len2 + 2;
new_string = malloc(new_len *sizeof(char));

if (new_string == NULL)
return (NULL);

for (i = 0; i < len1; i++)
new_string[i] = strct1[i];
new_string[i] = '/';

for (j = 0; j < len2; j++)
new_string[i + 1 + j] = strct2[j];
new_string[len1 + len2 + 1] = '\0';

return (new_string);
}
