/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ancanale <ancanale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 11:24:29 by ancanale          #+#    #+#             */
/*   Updated: 2025/10/08 10:58:37 by ancanale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <stddef.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <pthread.h>

typedef struct s_philo
{
	int			id;
	long long	last_meal;
	int			meals_eaten;
	pid_t		pid;
}	t_philo;

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	long long		start_time;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*table_sem;
	t_philo			*philos;
	int				dead;
}	t_data;

int			ft_atoi(const char *str);
void		init_data(t_data *data, int argc, char **argv);
void		init_philos(t_data *data);
void		philosopher_routine(t_data *data, t_philo *philo);
void		take_forks(t_data *data);
void		take_forks_with_print(t_data *data, int id);
void		eat(t_philo *philo, t_data *data);
void		put_forks(t_data *data);
void		sleep_philo(t_philo *philo, t_data *data);
void		think(t_philo *philo, t_data *data);
long long	get_time(void);
void		print_status(t_data *data, int id, char *status);
void		*death_monitor(void *arg);
void		cleanup(t_data *data);
void		kill_all_processes(t_data *data);

#endif
