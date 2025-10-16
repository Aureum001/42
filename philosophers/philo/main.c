/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:24:37 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/02 11:44:44 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	*philosopher_routine(void *arg)
{
	t_arg	*args;
	t_philo	*philo;
	t_data	*data;
	int		should_continue;

	args = (t_arg *)arg;
	philo = args->philo;
	data = args->data;
	while (1)
	{
		pthread_mutex_lock(&data->all_ate_mutex);
		should_continue = !data->dead && !data->all_ate;
		pthread_mutex_unlock(&data->all_ate_mutex);
		if (!should_continue)
			break ;
		think(philo, data);
		take_forks(philo, data);
		eat(philo, data);
		put_forks(philo, data);
		sleep_philo(philo, data);
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		should_continue;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->all_ate_mutex);
		should_continue = !data->dead && !data->all_ate;
		pthread_mutex_unlock(&data->all_ate_mutex);
		if (!should_continue)
			break ;
		if (check_death(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->all_ate_mutex);
	free(data->forks);
	free(data->philos);
}

void	create_threads(t_data *data, t_arg *args, pthread_t *monitor_thread)
{
	int	i;

	pthread_create(monitor_thread, NULL, monitor, data);
	i = 0;
	while (i < data->num_philos)
	{
		args[i].philo = &data->philos[i];
		args[i].data = data;
		pthread_create(&data->philos[i].thread, NULL,
			philosopher_routine, &args[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;
	t_arg		*args;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			argv[0]);
		return (1);
	}
	init_data(&data, argc, argv);
	init_philos(&data);
	args = malloc(sizeof(t_arg) * data.num_philos);
	create_threads(&data, args, &monitor_thread);
	pthread_join(monitor_thread, NULL);
	cleanup(&data);
	free(args);
	return (0);
}
