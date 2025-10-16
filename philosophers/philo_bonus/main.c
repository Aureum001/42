/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:24:37 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/08 10:58:18 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	*death_monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	data = (t_data *)((void **)arg)[0];
	philo = (t_philo *)((void **)arg)[1];
	while (1)
	{
		if (get_time() - philo->last_meal > data->time_to_die)
		{
			sem_wait(data->print_sem);
			printf("%lld %d died\n", get_time() - data->start_time, philo->id);
			exit(1);
		}
		usleep(1000);
	}
	return (NULL);
}

void	philosopher_routine(t_data *data, t_philo *philo)
{
	pthread_t	monitor_thread;
	void		*args[2];

	philo->last_meal = get_time();
	args[0] = data;
	args[1] = philo;
	pthread_create(&monitor_thread, NULL, death_monitor, args);
	pthread_detach(monitor_thread);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		think(philo, data);
		take_forks_with_print(data, philo->id);
		eat(philo, data);
		put_forks(data);
		if (data->must_eat > 0 && philo->meals_eaten >= data->must_eat)
			exit(0);
		sleep_philo(philo, data);
	}
}

void	kill_all_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].pid > 0)
			kill(data->philos[i].pid, SIGKILL);
		i++;
	}
}

void	create_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
		{
			philosopher_routine(data, &data->philos[i]);
			exit(0);
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		status;
	int		i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			argv[0]);
		return (1);
	}
	init_data(&data, argc, argv);
	init_philos(&data);
	create_processes(&data);
	waitpid(-1, &status, 0);
	kill_all_processes(&data);
	i = 0;
	while (i < data.num_philos)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	cleanup(&data);
	return (0);
}
