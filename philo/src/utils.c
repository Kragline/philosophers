/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:23:18 by armarake          #+#    #+#             */
/*   Updated: 2025/04/17 18:12:01 by armarake         ###   ########.fr       */
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

long long	ft_atoi(char *arg)
{
	long long	res;
	int			sign;

	sign = 1;
	res = 0;
	while (*arg && (*arg == 32 || (*arg >= 9 && *arg <= 13)))
		arg++;
	if (*arg == '-')
	{
		sign *= -1;
		arg++;
	}
	else if (*arg == '+')
		arg++;
	while (*arg && (*arg >= '0' && *arg <= '9'))
	{
		res = res * 10 + (*arg - '0');
		arg++;
	}
	return (res * sign);
}
