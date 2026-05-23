/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:58:49 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/23 09:21:14 by hrabh            ###   ########.fr       */
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

t_arg	*parsing(int argc, char **argv)
{
	int		i;
	t_arg	*argument;
	int		num;

	if (argc != 9)
		return (NULL);
	argument = malloc(sizeof(t_arg));
	i = 1;
	while (i < argc - 1 && strlen(argv[i]) < 11)
	{
		num = atoi(argv[i]);
		if (num != 0 || i == 7)
		{
			if (num < 0 || (i == 1 && num > 2000))
				return (NULL);
			helper_parsing(argument, i, num);
		}
		else
			return (NULL);
		i++;
	}
	if (check_scheduler(argument, argv[i]) == NULL)
		return (NULL);
	return (argument);
}
