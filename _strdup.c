#include "main.h"
/**
 * _strdup - this is used to duplicate a given string
 * @str: string to duplicated
 * Return: it return the copy of the given string
 */

char *_strdup(char *str)
{
        size_t lenght  = 0;
        size_t i;
        char *duplicate;

        lenght = _strlen(str);
        duplicate = (char *)malloc((lenght + 1) * sizeof(char));
        if (duplicate != NULL)
        {
                for (i = 0; i <= lenght; i++)
                {
                        duplicate[i] = str[i];
                }
        }
        return (duplicate);
}
