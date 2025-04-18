/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:23:32 by armarake          #+#    #+#             */
/*   Updated: 2025/04/18 15:10:47 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	allocate_data(t_data *data, int argc, char *argv[])
{
	data->number_of_philos = ft_atoi(argv[1]);
	if (argc == 6)
		data->number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philo_must_eat = -1;
	data->start_time = current_time();
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		printf("Mutex allocation failed\n");
		return (false);
	}
	return (true);
}

bool	allocate_mutexes(t_data *data, pthread_mutex_t *mutexes)
{
	int	i;

	mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->number_of_philos);
	if (!mutexes)
	{
		printf("Mutex allocation failed\n");
		return (false);
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_mutex_init(&mutexes[i++], NULL))
		{
			printf("Mutex allocation failed\n");
			destroy_all(data);
			return (false);
		}
	}
	data->mutexes = mutexes;
	return (true);
}

static bool	allocate_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]))
		{
			printf("Thread creation failed\n");
			destroy_all(data);
			return (false);
		}
		if (pthread_join(philos[i].thread, NULL))
		{
			printf("Thread joining failed\n");
			destroy_all(data);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	allocate_philos(t_data *data, t_philo *philos, char *argv[])
{
	int	i;

	philos = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philos);
	if (!philos)
		return (printf("Thread allocation failed\n"), false);
	i = 0;
	while (i < data->number_of_philos)
	{
		philos[i].index = i;
		philos[i].time_to_die = ft_atoi(argv[2]);
		philos[i].time_to_eat = ft_atoi(argv[3]);
		philos[i].time_to_sleep = ft_atoi(argv[4]);
		philos[i].eat_count = 0;
		philos[i].last_eat_time = current_time();
		philos[i].left_fork = &data->mutexes[i];
		allocate_threads(data, philos);
		if (i == 0)
			philos[i].right_fork = &data->mutexes[data->number_of_philos - 1];
		else
			philos[i].right_fork = &data->mutexes[i - 1];
		philos[i].print_mutex = &data->print_mutex;
		i++;
	}
	data->philos = philos;
	return (true);
}
