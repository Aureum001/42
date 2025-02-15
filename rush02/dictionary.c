#include "rush02.h" 
#include <stdlib.h>

// Esta función se encargará de abrir y parsear el archivo del diccionario. t_dictionary 
*parse_dictionary(const char *filepath); 
// TO DO: Implementar la lectura y el parseo del diccionario. 
// Debe seguir el formato: [número][espacios]:[espacios][cadena imprimible] 
// y crear una estructura t_dictionary con las entradas. 
// Aquí se devuelve una estructura dummy para la compilación. t_dictionary *dict;

/*
t_dictionary *dict;
dict = (t_dictionary *)malloc(sizeof(t_dictionary));
if (!dict)
	return (NULL);
dict->entries = NULL;
dict->size = 0;
return (dict);
*/

void free_dictionary(t_dictionary *dict) 
{ 
    int i;
    if (!dict)
	return ;
    i = 0;
    while (i < dict->size)
    {
        if (dict->entries[i].value)
            free(dict->entries[i].value);
        i++;
    }
    free(dict->entries);
    free(dict);
}