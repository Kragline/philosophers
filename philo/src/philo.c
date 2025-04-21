/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:37:12 by armarake          #+#    #+#             */
/*   Updated: 2025/04/21 21:57:41 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	pick_up_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_action(philo, "has taken a fork");
	}
}

static void	put_down_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
}

static void	eat(t_philo *philo)
{
	pick_up_forks(philo);
	print_action(philo, "is eating");
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
	print_action(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	print_action(philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_action(philo, "has taken a fork");
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	if (philo->index % 2 != 0)
		ft_usleep(1);
	while (true)
	{
		if (stop_loop(philo))
			break ;
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
