/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:24:29 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/17 09:29:54 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stddef.h>

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	long long	last_meal;
	int			meals_eaten;
	pthread_t	thread;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		start_time;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	all_ate_mutex;
	int				dead;
	int				all_ate;
}	t_data;

typedef struct s_arg
{
	t_philo	*philo;
	t_data	*data;
}	t_arg;

int			ft_atoi(const char *str);
int			init_data(t_data *data, int argc, char **argv);
void		init_philos(t_data *data);
int			check_death(t_data *data);
void		*philosopher_routine(void *arg);
void		take_forks(t_philo *philo, t_data *data);
void		eat(t_philo *philo, t_data *data);
void		put_forks(t_philo *philo, t_data *data);
void		check_meals(t_philo *philo, t_data *data);
void		sleep_philo(t_philo *philo, t_data *data);
void		think(t_philo *philo, t_data *data);
long long	get_time(void);
void		print_status(t_data *data, int id, char *status);
void		*monitor(void *arg);
void		cleanup(t_data *data);

#endif
