/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:45:41 by armarake          #+#    #+#             */
/*   Updated: 2025/04/24 16:14:57 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	check_ready(t_data *data)
{
	pthread_mutex_lock(&data->is_ready_mutex);
	if (data->is_ready)
		return (pthread_mutex_unlock(&data->is_ready_mutex), true);
	pthread_mutex_unlock(&data->is_ready_mutex);
	return (false);
}

void	wait_for_philos(t_data *data)
{
	while (true)
		if (check_ready(data))
			break ;
}

bool	start_simulation(t_data *data)
{
	allocate_threads(data);
	data->start_time = current_time();
	pthread_mutex_lock(&data->is_ready_mutex);
	data->is_ready = true;
	pthread_mutex_unlock(&data->is_ready_mutex);
	if (pthread_create(&data->monitor, NULL, monitoring_loop, data))
	{
		printf("Thread creation failed\n");
		destroy_all(data);
		return (false);
	}
	join_threads(data);
	return (true);
}
