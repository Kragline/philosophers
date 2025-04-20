/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:37:12 by armarake          #+#    #+#             */
/*   Updated: 2025/04/20 23:24:54 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	pick_up_forks(t_philo *philo)
{
	if (philo->index != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%ld %d has taken a fork\n", current_time()
			- philo->data->start_time, philo->index);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%ld %d has taken a fork\n", current_time()
			- philo->data->start_time, philo->index);
		pthread_mutex_unlock(philo->print_mutex);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%ld %d has taken a fork\n", current_time()
			- philo->data->start_time, philo->index);
		pthread_mutex_unlock(philo->print_mutex);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%ld %d has taken a fork\n", current_time()
			- philo->data->start_time, philo->index);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

static void	put_down_forks(t_philo *philo)
{
	if (philo->index != 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

static void	eat(t_philo *philo)
{
	pick_up_forks(philo);
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d is eating\n", current_time()
		- philo->data->start_time, philo->index);
	pthread_mutex_unlock(philo->print_mutex);
	pthread_mutex_lock(philo->last_eat_mutex);
	philo->last_eat_time = current_time();
	pthread_mutex_unlock(philo->last_eat_mutex);
	ft_usleep(philo->time_to_eat);
	put_down_forks(philo);
	pthread_mutex_lock(philo->eat_count_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(philo->eat_count_mutex);
}

static void	sleep_and_think(t_philo *philo)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d is sleeping\n", current_time()
		- philo->data->start_time, philo->index);
	pthread_mutex_unlock(philo->print_mutex);
	ft_usleep(philo->time_to_sleep);
	pthread_mutex_lock(philo->print_mutex);
	printf("%ld %d is thinking\n", current_time()
		- philo->data->start_time, philo->index);
	pthread_mutex_unlock(philo->print_mutex);
}

static	bool	stop_loop(t_philo	*philo)
{
	pthread_mutex_lock(philo->someone_died_mutex);
	if (philo->data->someone_dead)
		return (pthread_mutex_unlock(philo->someone_died_mutex), true);
	pthread_mutex_unlock(philo->someone_died_mutex);
	return (false);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->print_mutex);
		printf("%ld %d has taken a fork\n", current_time()
			- philo->data->start_time, philo->index);
		pthread_mutex_unlock(philo->print_mutex);
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->index % 2 == 0)
		ft_usleep(10);
	while (true)
	{
		if (stop_loop(philo))
			break ;
		eat(philo);
		sleep_and_think(philo);
	}
	printf("thread finished (%d)\n\n", philo->index);
	return (NULL);
}
