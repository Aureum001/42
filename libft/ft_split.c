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

static int	count_words(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s != c)
			s++;
	}
	return (count);
}

static char	*allocate_word(char const *s, char c, char **strs)
{
	char	*word;
	
	word = ft_strchr(s, c);
	if (!word || !c)
	{
		word = (char *)s;
		while (*word)
			word++;
	}
	*strs = ft_substr(s, 0, word - s);
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	char	**buf;

	if (!s)
		return (NULL);
	strs = (char **)malloc((count_words(s, c) + 1) * sizeof(*strs));
	if (!strs)
		return (NULL);
	buf = strs;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			s = allocate_word(s, c, strs++);
	}
	*strs = 0;
	return (buf);
}
