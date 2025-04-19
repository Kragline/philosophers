/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:23:32 by armarake          #+#    #+#             */
/*   Updated: 2025/04/20 00:49:04 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	allocate_mutexes(t_data *data)
{
	int	i;

	data->mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_of_philos);
	if (!data->mutexes)
	{
		printf("Mutex allocation failed\n");
		return (false);
	}
	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_mutex_init(&data->mutexes[i++], NULL))
		{
			printf("Mutex allocation failed\n");
			destroy_all(data);
			return (false);
		}
	}
	return (true);
}

static bool	allocate_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i]))
		{
			printf("Thread creation failed\n");
			destroy_all(data);
			return (false);
		}
		i++;
	}
	return (true);
}

static void	philo_forks(t_data *data, int i)
{
	if (i == 0)
		data->philos[i].right_fork = &data->mutexes[data->num_of_philos - 1];
	else
		data->philos[i].right_fork = &data->mutexes[i - 1];
}

static bool	allocate_philos(t_data *data, char *argv[])
{
	int	i;

	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (printf("Thread allocation failed\n"), false);
	i = 0;
	while (i < data->num_of_philos)
	{
		data->philos[i].index = i;
		data->philos[i].num_of_philos = ft_atoi(argv[1]);
		data->philos[i].time_to_die = ft_atoi(argv[2]);
		data->philos[i].time_to_eat = ft_atoi(argv[3]);
		data->philos[i].time_to_sleep = ft_atoi(argv[4]);
		data->philos[i].eat_count = 0;
		data->philos[i].last_eat_time = current_time();
		data->philos[i].left_fork = &data->mutexes[i];
		philo_forks(data, i);
		data->philos[i].print_mutex = &data->print_mutex;
		data->philos[i].change_val_mutex = &data->change_val_mutex;
		i++;
	}
	allocate_threads(data);
	return (true);
}

bool	allocate_data(t_data *data, int argc, char *argv[])
{
	data->philos = NULL;
	data->mutexes = NULL;
	data->num_of_philos = ft_atoi(argv[1]);
	if (argc == 6)
		data->number_of_times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philo_must_eat = -1;
	data->start_time = current_time();
	if (pthread_mutex_init(&data->change_val_mutex, NULL))
	{
		printf("Mutex allocation failed\n");
		return (false);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		printf("Mutex allocation failed\n");
		return (false);
	}
	if (!allocate_mutexes(data))
		return (false);
	if (!allocate_philos(data, argv))
		return (false);
	return (true);
}
