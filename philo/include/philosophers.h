/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:45:05 by armarake          #+#    #+#             */
/*   Updated: 2025/04/18 15:08:50 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>

typedef struct s_philo
{
	int				index;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	uint64_t		last_eat_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
}	t_philo;

typedef struct s_data
{
	int				number_of_philos;
	int				number_of_times_each_philo_must_eat;
	uint64_t		start_time;
	t_philo			*philos;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	print_mutex;
}	t_data;

//			utils
uint64_t	current_time(void);
void		ft_usleep(unsigned int milliseconds);
long long	ft_atoi(char *arg);

//			validation
bool		check_input(int argc, char *argv[]);

//			allocation
bool		allocate_data(t_data *philo, int argc, char *argv[]);
bool		allocate_mutexes(t_data *data, pthread_mutex_t *mutexes);
bool		allocate_philos(t_data *data, t_philo *philos, char *argv[]);

//			destroy
void		destroy_all(t_data *data);

//			philo
void		*routine(void *philo);

#endif