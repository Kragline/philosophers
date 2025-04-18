/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:45:37 by armarake          #+#    #+#             */
/*   Updated: 2025/04/18 15:12:44 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char *argv[])
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*mutexes;

	if (!check_input(argc, argv))
		return (1);
	philos = NULL;
	mutexes = NULL;
	data.philos = NULL;
	data.mutexes = NULL;
	if (!allocate_data(&data, argc, argv))
		return (1);
	if (!allocate_mutexes(&data, mutexes))
		return (1);
	if (!allocate_philos(&data, philos, argv))
		return (1);
	destroy_all(&data);
	return (0);
}
