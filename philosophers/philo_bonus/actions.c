/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:24:43 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/08 10:07:59 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

void	take_forks(t_data *data)
{
	sem_wait(data->table_sem);
	sem_wait(data->forks);
	sem_wait(data->forks);
}

void	take_forks_with_print(t_data *data, int id)
{
	sem_wait(data->table_sem);
	sem_wait(data->forks);
	print_status(data, id, "has taken a fork");
	sem_wait(data->forks);
	print_status(data, id, "has taken a fork");
}

void	eat(t_philo *philo, t_data *data)
{
	print_status(data, philo->id, "is eating");
	philo->last_meal = get_time();
	philo->meals_eaten++;
	usleep(data->time_to_eat * 1000);
}

void	put_forks(t_data *data)
{
	sem_post(data->forks);
	sem_post(data->forks);
	sem_post(data->table_sem);
}
