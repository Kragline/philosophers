/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:19:08 by armarake          #+#    #+#             */
/*   Updated: 2025/04/17 22:16:05 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->number_of_philos)
		pthread_mutex_destroy(&data->mutexes[i]);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->mutexes);
	data->mutexes = NULL;
}

void	destroy_philos(t_data *data)
{
	free(data->philos);
	data->philos = NULL;
}
