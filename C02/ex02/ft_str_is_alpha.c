/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:36:37 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/05 14:55:31 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	is_lower(char c)
{
	return (c <= 'z' && c >= 'a');
}

char	is_upper(char c)
{
	return (c <= 'Z' && c >= 'A');
}

int	ft_str_is_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(is_lower(str[i]) || is_upper(str[i])))
			return (0);
		i++;
	}
	return (1);
}
