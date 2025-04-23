/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:45:05 by armarake          #+#    #+#             */
/*   Updated: 2025/04/24 00:37:11 by armarake         ###   ########.fr       */
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
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	uint64_t		last_eat_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*is_ready_mutex;
	pthread_mutex_t	*last_eat_mutex;
	pthread_mutex_t	*stop_program_mutex;
	pthread_mutex_t	*eat_count_mutex;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				num_of_philos;
	int				number_to_eat;
	bool			is_ready;
	bool			stop_program;
	uint64_t		start_time;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	is_ready_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	stop_program_mutex;
	pthread_mutex_t	eat_count_mutex;
}	t_data;

//				utils
uint64_t	current_time(void);
void		ft_usleep(unsigned int milliseconds);
long long	ft_atoi(char *arg);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
bool		join_threads(t_data *data);

//				validation
bool		check_input(int argc, char *argv[]);

//				allocation
bool		allocate_data(t_data *philo, int argc, char *argv[]);
bool		allocate_data_mutexes(t_data *data);
void		allocate_philo_mutexes(t_data *data, int i);
bool		allocate_threads(t_data *data);

//				simulation
bool		start_simulation(t_data *data);

//				monitoring
void		*monitoring_loop(void *arg);

//				destroy
void		destroy_all(t_data *data);

//				philo
void		*routine(void *philo);
void		print_action(t_philo *philo, char *msg);
bool		stop_loop(t_philo *philo);
void		wait_for_philos(t_data *data);

#endif