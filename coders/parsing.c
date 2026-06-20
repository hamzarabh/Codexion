/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:58:49 by hrabh             #+#    #+#             */
/*   Updated: 2026/06/17 22:20:02 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

static void	helper_parsing(t_arg *argument, int index, int num)
{
	if (index == 1)
		argument->number_of_coders = num;
	if (index == 2)
		argument->time_to_burnout = num;
	if (index == 3)
		argument->time_to_compile = num;
	if (index == 4)
		argument->time_to_debug = num;
	if (index == 5)
		argument->time_to_refactor = num;
	if (index == 6)
		argument->number_of_compiles_required = num;
	if (index == 7)
		argument->dongle_cooldown = num;
}

static void	*check_scheduler(t_arg *argument, char *scheduler)
{
	if (strcmp(scheduler, "fifo") == 0)
	{
		argument->scheduler = scheduler;
		return (argument);
	}
	else if (strcmp(scheduler, "edf") == 0)
	{
		argument->scheduler = scheduler;
		return (argument);
	}
	else
		return (NULL);
}

static	int	check_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++ ;
	while (str[i] == '0')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		if (strlen(&str[i]) > 10)
			return (0);
		i++;
	}
	return (1);
}

t_arg	*parsing(int argc, char **argv)
{
	int		i;
	t_arg	*argument;
	int		num;

	argument = malloc(sizeof(t_arg));
	if (!argument)
		return (NULL);
	i = 1;
	while (i < argc - 1 && check_digit(argv[i]) == 1)
	{
		num = atoi(argv[i]);
		if (num != 0 || i == 7)
		{
			if (num < 0 || (i == 1 && num > 2000))
				return (NULL);
			helper_parsing(argument, i, num);
		}
		else
			return (free(argument), NULL);
		i++;
	}
	if (check_scheduler(argument, argv[i]) == NULL)
		return (free(argument), NULL);
	return (argument);
}
