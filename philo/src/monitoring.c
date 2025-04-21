/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:16:24 by armarake          #+#    #+#             */
/*   Updated: 2025/04/21 17:14:11 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	someone_died(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(data->philos[i].last_eat_mutex);
		if (current_time() - data->philos[i].last_eat_time
			> (uint64_t)data->philos[i].time_to_die)
		{
			pthread_mutex_lock(data->philos[i].print_mutex);
			printf("%ld %d died\n", current_time() - data-> start_time,
				data->philos[i].index + 1);
			pthread_mutex_unlock(data->philos[i].print_mutex);
			pthread_mutex_lock(data->philos[i].someone_died_mutex);
			data->someone_dead = true;
			pthread_mutex_unlock(data->philos[i].someone_died_mutex);
			pthread_mutex_unlock(data->philos[i].last_eat_mutex);
			return (true);
		}
		pthread_mutex_unlock(data->philos[i].last_eat_mutex);
		i++;
	}
	return (false);
}

static bool	finished_eating(t_data *data)
{
	int	i;
	int	finished_count;

	i = 0;
	finished_count = 0;
	if (data->num_of_philos == -1)
		return (false);
	while (i < data->number_to_eat)
	{
		pthread_mutex_lock(data->philos[i].eat_count_mutex);
		if (data->philos[i].eat_count >= data->number_to_eat)
			finished_count++;
		pthread_mutex_lock(data->philos[i].print_mutex);
		printf("%d %d %d\n", finished_count, data->number_to_eat, data->philos[i].eat_count);
		pthread_mutex_unlock(data->philos[i].print_mutex);
		pthread_mutex_unlock(data->philos[i].eat_count_mutex);
		i++;
	}
	return (finished_count == data->num_of_philos);
}

void	monitoring(t_data *data)
{
	while (true)
	{
		if (finished_eating(data))
			return ;
		if (someone_died(data))
			return ;
	}
}
