/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:40:20 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/10 16:17:02 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *str, char *to_find)
{
	char	*a;
	char	*b;

	b = to_find;
	if (*b == '\0')
		return (str);
	while (*str)
	{
		if (*str == *b)
		{
			a = str;
			while ((*a) && (*b) && (*a == *b))
			{
				a++;
				b++;
			}
			if (*b == '\0')
				return (str);
			b = to_find;
		}
		str++;
	}
	return (0);
}
