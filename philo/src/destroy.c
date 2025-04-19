/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:19:08 by armarake          #+#    #+#             */
/*   Updated: 2025/04/19 17:33:03 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
		pthread_mutex_destroy(&data->mutexes[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->change_val_mutex);
	free(data->mutexes);
	data->mutexes = NULL;
}

static void	destroy_philos(t_data *data)
{
	free(data->philos);
	data->philos = NULL;
}

void	destroy_all(t_data *data)
{
	if (data->mutexes)
		destroy_mutexes(data);
	if (data->philos)
		destroy_philos(data);
}
