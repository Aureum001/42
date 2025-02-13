/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 17:28:31 by ancanale          #+#    #+#             */
/*   Updated: 2025/02/05 18:05:02 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	is_lower(char c)
{
	return (c <= 'z' && c >= 'a');
}

char	is_numeric(char c)
{
	return (c <= '9' && c >= '0');
}

char	*ft_strcapitalize(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 1;
	while (str[i])
	{
		if ((flag) && (is_lower(str[i])))
		{
			str[i] -= 32;
			flag = 0;
		}
		else if (str[i] == ' ' || str[i] == '+' || str[i] == '-')
			flag = 1;
		else if (is_numeric(str[i]))
			flag = 0;
		i++;
	}
	return (str);
}
