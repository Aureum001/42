/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:24:40 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/08 10:11:35 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	init_data(t_data *data, int argc, char **argv)
{
	int	table_limit;
	
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	data->start_time = get_time();
	data->dead = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/table");
	data->forks = sem_open("/forks", O_CREAT, 0644, data->num_philos);
	data->print_sem = sem_open("/print", O_CREAT, 0644, 1);
	table_limit = data->num_philos / 2;
	if (table_limit == 0)
		table_limit = 1;
	data->table_sem = sem_open("/table", O_CREAT, 0644, table_limit);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].meals_eaten = 0;
		data->philos[i].pid = -1;
		i++;
	}
}
