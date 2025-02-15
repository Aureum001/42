/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:45:21 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/14 22:45:21 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rush02.h>

int is_valid_number(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
            i++;
    }
    return (1);
}

int main(int argc, char **argv)
{
    char *number_str;
    char *dict_path;
        // Comprobación de argumentos: debe ser 2 o 3 (recordando que argv[0] es el nombre del ejecutable)
    if (argc < 2 || argc > 3)
    {
        write(1, "Error\n", 6);
        return 1;
    }

    if (argc == 2)
    {
        dict_path = DEFAULT_DICT;
        number_str = argv[1];
    }
    else // argc == 3
    {
        dict_path = argv[1];
        number_str = argv[2];
    }

    // Validamos que el número recibido contenga únicamente dígitos.
    if (!is_valid_number(number_str))
    {
        write(1, "Error\n", 6);
        return 1;
    }

    // En este punto, ya tenemos la ruta del diccionario y el número a convertir.
    // Continuaremos con la lectura y el parseo del diccionario.
    // ...

    // Parseo del diccionario
    dict = parse_dictionary(dict_path);
    if (!dict)
    {
        write(1, "Dict Error\n", 11);
        return (1);
    }

    // Conversión del número a palabras
    result = convert_number_to_words(number_str, dict);
    if (!result)
    {
        write(1, "Dict Error\n", 11);
        free_dictionary(dict);
        return (1);
    }

    // Salida: imprimir el resultado
    ft_putstr(result);
    write(1, "\n", 1);

    // Liberar recursos
    free(result);
    free_dictionary(dict);
    return (0);
}