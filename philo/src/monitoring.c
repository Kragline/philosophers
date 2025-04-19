/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:16:24 by armarake          #+#    #+#             */
/*   Updated: 2025/04/19 17:42:02 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->change_val_mutex);
	if (current_time() - philo->last_eat_time > (uint64_t)philo->time_to_die)
		return (pthread_mutex_unlock(philo->change_val_mutex), true);
	pthread_mutex_unlock(philo->change_val_mutex);
	return (false);
}

bool	monitoring(t_data *data)
{
	int	i;

	while (true)
	{
		i = 0;
		while (i < data->num_of_philos)
		{
			if (is_dead(&data->philos[i]))
				return (die_msg(&data->philos[i]), destroy_all(data), false);
			i++;
		}
	}
	return (true);
}