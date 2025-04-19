/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armarake <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:34:26 by armarake          #+#    #+#             */
/*   Updated: 2025/04/19 14:31:27 by armarake         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static bool	is_all_num(char *arg)
{
	while (*arg)
	{
		if (!(*arg >= '0' && *arg <= '9') && !(*arg == '+' || *arg == '-'))
			return (printf("Argument in not numeric\n\033[0;37m"), false);
		arg++;
	}
	return (true);
}

static bool	is_empty(char *arg)
{
	if (*arg == '\0')
		return (printf("Argumment can not be empty\n\033[0;37m"), false);
	return (true);
}

static void	help_message(void)
{
	printf("\033[0;37m");
	printf("Run program as follows\n\n");
	printf("\033[1;35m");
	printf("./philo ");
	printf("\033[0;37m");
	printf("number_of_philosophers time_to_die time_to_eat time_to_sleep ");
	printf("\033[0;32m");
	printf("number_of_times_each_philosopher_must_eat\n\n");
	printf("Note: last argument is optional\n");
	printf("\033[0;37m");
}

static void	wrong_number_of_arguments(void)
{
	printf("Wrong number of arguments\n");
	printf("\033[0;37m");
	printf("Use ./philo --help to see right usage\n");
}

bool	check_input(int argc, char *argv[])
{
	int	i;

	i = 1;
	if (argc == 2 && ft_strncmp(argv[1], "--help", 6) == 0)
		return (help_message(), false);
	printf("\033[1;31m");
	if (argc < 5 || argc > 6)
		return (wrong_number_of_arguments(), 0);
	while (i < argc)
	{
		if (!is_empty(argv[i]))
			return (false);
		if (!is_all_num(argv[i]))
			return (false);
		if (ft_atoi(argv[i]) > INT_MAX || ft_atoi(argv[i]) < 1)
			return (printf("Argumment can not be negative\n\033[0;37m"), 0);
		i++;
	}
	printf("\033[0;37m");
	return (true);
}
