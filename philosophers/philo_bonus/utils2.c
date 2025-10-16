/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 10:13:37 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/08 10:14:01 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	cleanup(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print_sem);
	sem_close(data->table_sem);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/table");
	free(data->philos);
}