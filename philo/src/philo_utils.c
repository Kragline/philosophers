/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 23:39:56 by armarake          #+#    #+#             */
/*   Updated: 2025/04/24 16:14:53 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_action(t_philo *philo, char *msg)
{
	uint64_t	timesnap;

	timesnap = current_time() - philo->data->start_time;
	pthread_mutex_lock(philo->print_mutex);
	if (!stop_loop(philo))
		printf("%ld %d %s\n", timesnap, philo->index, msg);
	pthread_mutex_unlock(philo->print_mutex);
}

bool	stop_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->stop_program_mutex);
	if (philo->data->stop_program)
		return (pthread_mutex_unlock(philo->stop_program_mutex), true);
	pthread_mutex_unlock(philo->stop_program_mutex);
	return (false);
}
