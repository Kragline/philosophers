/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:45:41 by armarake          #+#    #+#             */
/*   Updated: 2025/04/24 00:43:58 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

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
