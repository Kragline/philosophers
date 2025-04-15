/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:23:18 by armarake          #+#    #+#             */
/*   Updated: 2025/04/15 20:01:47 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

uint64_t	current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(unsigned int milliseconds)
{
	uint64_t	start;

	start = current_time();
	while ((current_time() - start) < milliseconds)
		usleep(1);
}
