/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:24:47 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/08 10:58:07 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_status(t_data *data, int id, char *status)
{
	char	*colors[7];
	char	*reset;
	int		color_index;

	reset = "\033[0m";
	colors[0] = "\033[31m";
	colors[1] = "\033[32m";
	colors[2] = "\033[33m";
	colors[3] = "\033[34m";
	colors[4] = "\033[35m";
	colors[5] = "\033[36m";
	colors[6] = "\033[37m";
	color_index = (id - 1) % 7;
	sem_wait(data->print_sem);
	printf("%s%lld %d %s%s\n", colors[color_index], get_time()
		- data->start_time, id, status, reset);
	sem_post(data->print_sem);
}

void	sleep_philo(t_philo *philo, t_data *data)
{
	print_status(data, philo->id, "is sleeping");
	usleep(data->time_to_sleep * 1000);
}

void	think(t_philo *philo, t_data *data)
{
	print_status(data, philo->id, "is thinking");
}
