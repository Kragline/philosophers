/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:35:43 by armarake          #+#    #+#             */
/*   Updated: 2025/04/20 23:38:50 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	allocate_data_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->eat_count_mutex, NULL))
	{
		printf("Mutex allocation failed\n");
		return (false);
	}
	if (pthread_mutex_init(&data->last_eat_mutex, NULL))
	{
		printf("Mutex allocation failed\n");
		return (false);
	}
	if (pthread_mutex_init(&data->someone_died_mutex, NULL))
	{
		printf("Mutex allocation failed\n");
		return (false);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		printf("Mutex allocation failed\n");
		return (false);
	}
	return (true);
}

void	allocate_philo_mutexes(t_data *data, int i)
{
	data->philos[i].left_fork = &data->mutexes[i];
	if (i == 0)
		data->philos[i].right_fork = &data->mutexes[data->num_of_philos - 1];
	else
		data->philos[i].right_fork = &data->mutexes[i - 1];
	data->philos[i].print_mutex = &data->print_mutex;
	data->philos[i].last_eat_mutex = &data->last_eat_mutex;
	data->philos[i].someone_died_mutex = &data->someone_died_mutex;
	data->philos[i].eat_count_mutex = &data->eat_count_mutex;
}
