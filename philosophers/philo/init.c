/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:24:40 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/17 09:34:02 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

static void	destroy_mutexes(t_data *data, int forks_count, int has_print,
		int has_all_ate)
{
	int	i;

	i = forks_count - 1;
	while (i >= 0)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i--;
	}
	if (has_all_ate)
		pthread_mutex_destroy(&data->all_ate_mutex);
	if (has_print)
		pthread_mutex_destroy(&data->print_mutex);
}

static int	init_mutexes(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->all_ate_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			destroy_mutexes(data, i, 1, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
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
	data->all_ate = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->forks || !data->philos)
		return (1);
	return (init_mutexes(data));
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->num_philos;
		data->philos[i].last_meal = data->start_time;
		data->philos[i].meals_eaten = 0;
		i++;
	}
}

int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (get_time() - data->philos[i].last_meal > data->time_to_die)
		{
			print_status(data, data->philos[i].id, "died");
			pthread_mutex_lock(&data->all_ate_mutex);
			data->dead = 1;
			pthread_mutex_unlock(&data->all_ate_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}
