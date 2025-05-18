/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:40:58 by ancanale          #+#    #+#             */
/*   Updated: 2025/05/18 14:18:52 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_fd_list
{
	int					fd;
	char				*buffer;
	struct s_fd_list	*next;
}	t_fd_list;

char		*get_next_line(int fd);
t_fd_list	*find_fd_node(t_fd_list **list, int fd);
t_fd_list	*create_fd_node(int fd);
void		free_fd_node(t_fd_list **list, int fd);

#endif