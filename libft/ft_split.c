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

static int	ft_word_len(char const *str, char sep)
{
	int	len;

	len = 0;
	while (str[len] && !(str[len] == sep))
		len++;
	return (len);
}

static char	*allocate_word(char const *str, char sep)
{
	int		len;
	int		i;
	char	*word;

	i = 0;
	len = ft_word_len(str, sep);
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

char	**ft_split(char const *str, char sep)
{
	int		i;
	int		n_words;
	char	**strings;

	i = 0;
	if (!str)
		return (NULL);
	n_words = count_words(str, sep);
	strings = (char **)malloc(sizeof(char *) * (n_words + 1));
	while (*str)
	{
		while (*str && *str == sep)
			str++;
		if (*str)
		{
			strings[i] = allocate_word(str, sep);
			if (!strings[i])
				return (NULL);
			i++;
		}
		while (*str && !(*str == sep))
			str++;
	}
	strings[i] = NULL;
	return (strings);
}

// static int	count_words(char const *s, char c)
// {
// 	int	count;

// 	count = 0;
// 	while (*s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s)
// 			count++;
// 		while (*s != c)
// 			s++;
// 	}
// 	return (count);
// }

// static char	*allocate_word(char const *s, char c, char **strs)
// {
// 	char	*word;
// 	word = ft_strchr(s, c);
// 	if (!word || !c)
// 	{
// 		word = (char *)s;
// 		while (*word)
// 			word++;
// 	}
// 	*strs = ft_substr(s, 0, word - s);
// 	return (word);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**strs;
// 	char	**buf;

// 	if (!s)
// 		return (NULL);
// 	strs = (char **)malloc((count_words(s, c) + 1) * sizeof(*strs));
// 	if (!strs)
// 		return (NULL);
// 	buf = strs;
// 	while (*s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s)
// 			s = allocate_word(s, c, strs++);
// 	}
// 	*strs = 0;
// 	return (buf);
// }
