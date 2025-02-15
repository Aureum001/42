#include "rush02.h"

void ft_putstr(char *str) 
{ 
    int i;

    if (!str)
        return ;
    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
}

char *ft_strdup(const char *src) 
{ 
    char *dup; 
    int len; 
    int i;

    len = 0;
    while (src[len])
        len++;
    dup = (char *)malloc(len + 1);
    if (!dup)
        return (NULL);
    i = 0;
    while (src[i])
    {
        dup[i] = src[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);

}

// Ejemplo básico de función ft_strtrim. 
// TO DO: Mejorar la función para eliminar espacios al principio y al final. 
char *ft_strtrim(char *str) 
{ 
// Por ahora, simplemente retorna el mismo string. 
    return (str); 
}