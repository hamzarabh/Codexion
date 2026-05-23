/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:57:29 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/22 19:00:49 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

static pthread_t	*create_coders(t_coder **coders)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * coders[0]->args->number_of_coders);
	if (!threads)
		return (NULL);
	while (i < coders[0]->args->number_of_coders)
	{
		if (pthread_create(&threads[i], NULL, simulation, coders[i]) != 0)
			return (NULL);
		i++;
	}
	return (threads);
}

int	ft_creator(t_coder **coders)
{
	int			i;
	pthread_t	*threads;
	pthread_t	monitor;

	i = 0;
	threads = create_coders(coders);
	if (!threads)
		return (1);
	if (pthread_create(&monitor, NULL, ft_monitor, coders) != 0)
		return (1);
	i = 0;
	while (i < coders[0]->args->number_of_coders)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (1);
		i++;
	}
	pthread_mutex_lock(&coders[0]->args->stop_lock);
	*coders[0]->args->stop = 0;
	pthread_mutex_unlock(&coders[0]->args->stop_lock);
	pthread_join(monitor, NULL);
	free(threads);
	return (0);
}
