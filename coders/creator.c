/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 03:39:05 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/21 12:42:03 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

pthread_t	*create_coders(coder_t **coders)
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

int	ft_creator(coder_t **coders)
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
