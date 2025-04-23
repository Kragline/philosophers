/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:16:24 by armarake          #+#    #+#             */
/*   Updated: 2025/04/23 16:16:46 by armarake         ###   ########.fr       */
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
			print_action(&data->philos[i], "died");
			pthread_mutex_lock(data->philos[i].stop_program_mutex);
			data->stop_program = true;
			pthread_mutex_unlock(data->philos[i].stop_program_mutex);
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
	if (data->number_to_eat == -1)
		return (false);
	while (i < data->num_of_philos)
	{
		pthread_mutex_lock(data->philos[i].eat_count_mutex);
		if (data->philos[i].eat_count >= data->number_to_eat)
			finished_count++;
		pthread_mutex_unlock(data->philos[i].eat_count_mutex);
		i++;
	}
	if (finished_count >= data->num_of_philos)
	{
		pthread_mutex_lock(&data->stop_program_mutex);
		data->stop_program = true;
		pthread_mutex_unlock(&data->stop_program_mutex);
		return (true);
	}
	return (false);
}

void	monitoring(t_data *data)
{
	while (true)
	{
		if (finished_eating(data) || someone_died(data))
			return ;
		usleep(data->num_of_philos * 1000);
	}
}
