/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 10:25:15 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/18 15:52:10 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fd_list	*find_fd_node(t_fd_list **list, int fd)
{
	t_fd_list	*current;

	if (!list)
		return (NULL);
	current = *list;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_fd_list	*create_fd_node(int fd)
{
	t_fd_list	*new_node;

	new_node = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->buffer = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	search_and_free(t_fd_list *prev, t_fd_list *current, int fd)
{
	while (current)
	{
		if (current->fd == fd)
		{
			prev->next = current->next;
			free(current->buffer);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	free_fd_node(t_fd_list **list, int fd)
{
	t_fd_list	*current;
	t_fd_list	*prev;

	if (!list || !*list)
		return ;
	if ((*list)->fd == fd)
	{
		current = *list;
		*list = (*list)->next;
		free(current->buffer);
		free(current);
		return ;
	}
	prev = *list;
	current = prev->next;
	search_and_free(prev, current, fd);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

static size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*buf;

	buf = src;
	if (src && dst && size)
	{
		while (*src && --size)
			*dst++ = *src++;
		*dst = 0;
	}
	return (ft_strlen(buf));
}

char	*ft_strchr(const char *str, int c)
{
	if (!str)
		return (NULL);
	while (*str)
		if (*str++ == (char) c)
			return ((char *)(str - 1));
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(*str) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, len1 + 1);
	ft_strlcpy(str + len1, s2, len2 + 1);
	return (str);
}

char	*ft_strdup(const char *src)
{
	char	*str;
	size_t	len;

	if (!src)
	{
		str = malloc(1);
		if (!str)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	len = ft_strlen(src);
	str = malloc(sizeof(*src) * (len + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, src, len + 1);
	return (str);
}