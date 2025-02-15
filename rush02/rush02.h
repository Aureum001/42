#ifndef RUSH02_H

#define RUSH02_H
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#define DEFAULT_DICT "numbers.dict"
typedef struct s_dict_entry { unsigned int key; char *value; } t_dict_entry;

typedef struct s_dictionary { t_dict_entry *entries; int size; } t_dictionary;

// Funciones de validación y parseo int is_valid_number(const char *str); t_dictionary *parse_dictionary(const char *filepath); void free_dictionary(t_dictionary *dict);
t_dictionary *parse_dictionary(const char *filepath); 
void free_dictionary(t_dictionary *dict);
// Función de conversión char *convert_number_to_words(const char *number_str, t_dictionary *dict);

// Funciones utilitarias void ft_putstr(char *str); char *ft_strdup(const char *src); char *ft_strtrim(char *str);

#endif