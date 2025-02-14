/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 21:59:12 by marvin            #+#    #+#             */
/*   Updated: 2025/02/14 21:59:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(int argc, char **argv)
{
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

    return (0);

}