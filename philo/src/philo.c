/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:37:12 by armarake          #+#    #+#             */
/*   Updated: 2025/04/19 18:24:37 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	pich_up_forks(t_philo *philo)
{
	if (philo->index != 0)
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken a fork\n", current_time(), philo->index);
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taken a fork\n", current_time(), philo->index);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%ld %d has taken a fork\n", current_time(), philo->index);
		pthread_mutex_lock(philo->right_fork);
		printf("%ld %d has taken a fork\n", current_time(), philo->index);
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

void	eat(t_philo *philo)
{
	pich_up_forks(philo);
	printf("%ld %d is eating\n", current_time(), philo->index);
	put_down_forks(philo);
	pthread_mutex_lock(philo->change_val_mutex);
	philo->last_eat_time = current_time();
	pthread_mutex_unlock(philo->change_val_mutex);
	ft_usleep(philo->time_to_eat);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		eat(philo);
		printf("%ld %d is sleeping\n", current_time(), philo->index);
		ft_usleep(philo->time_to_sleep);
		printf("%ld %d is thinking\n", current_time(), philo->index);
	}
	return (NULL);
}
