/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:24:43 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/02 11:38:04 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	take_forks(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_status(data, philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		print_status(data, philo->id, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		print_status(data, philo->id, "has taken a fork");
	}
}

void	eat(t_philo *philo, t_data *data)
{
	print_status(data, philo->id, "is eating");
	philo->last_meal = get_time();
	philo->meals_eaten++;
	usleep(data->time_to_eat * 1000);
	check_meals(philo, data);
}

void	put_forks(t_philo *philo, t_data *data)
{
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	print_status(data, philo->id, "is sleeping");
}

void	check_meals(t_philo *philo, t_data *data)
{
	int	i;
	int	all_finished;

	(void)philo;
	if (data->must_eat <= 0)
		return ;
	pthread_mutex_lock(&data->print_mutex);
	i = 0;
	all_finished = 1;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->must_eat)
		{
			all_finished = 0;
			break ;
		}
		i++;
	}
	if (all_finished)
	{
		pthread_mutex_lock(&data->all_ate_mutex);
		data->all_ate = 1;
		pthread_mutex_unlock(&data->all_ate_mutex);
	}
	pthread_mutex_unlock(&data->print_mutex);
}
