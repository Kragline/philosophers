/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 23:45:37 by armarake          #+#    #+#             */
/*   Updated: 2025/04/20 22:45:13 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char *argv[])
{
	t_data			data;

	if (!check_input(argc, argv))
		return (1);
	if (!allocate_data(&data, argc, argv))
		return (1);
	monitoring(&data);
	if (!join_threads(&data))
		return (1);
	destroy_all(&data);
	return (0);
}
