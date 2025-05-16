/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <antonioayr.94@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:50:45 by ancanale          #+#    #+#             */
/*   Updated: 2025/03/04 09:50:45 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_and_return(char **strings, int i)
{
	while (i--)
		free(strings[i]);
	free(strings);
	return (NULL);
}

static int	count_words(char const *str, char sep)
{
	int	i;
	int	n_words;

	i = 0;
	n_words = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
			n_words++;
		while (str[i] && !(str[i] == sep))
			i++;
	}
	return (n_words);
}

static char	*allocate_word(char const *str, char sep)
{
	int		len;
	int		i;
	char	*word;

	i = 0;
	len = 0;
	while (str[len] && !(str[len] == sep))
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**process_words(char const *str, char sep, char **strings)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str && *str == sep)
			str++;
		if (*str)
		{
			strings[i] = allocate_word(str, sep);
			if (!strings[i])
				return (free_and_return(strings, i));
			i++;
		}
		while (*str && !(*str == sep))
			str++;
	}
	strings[i] = NULL;
	return (strings);
}

char	**ft_split(char const *str, char sep)
{
	char	**strings;

	if (!str)
		return (NULL);
	strings = (char **)malloc(sizeof(char *) * (count_words(str, sep) + 1));
	if (!strings)
		return (NULL);
	return (process_words(str, sep, strings));
}
