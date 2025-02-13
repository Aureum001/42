/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_program_name.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:12:07 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/13 14:26:49 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	main(__attribute__((unused)) int argc, char **argv)
{
	char	*pname;

	pname = argv[0];
	while (*pname)
		write(1, pname++, 1);
	return (0);
}
