/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:58:34 by hrabh             #+#    #+#             */
/*   Updated: 2026/06/20 20:35:07 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

static void	ft_free(t_coder **coders)
{
	int	n_coder;
	int	i;

	i = 0;
	n_coder = coders[0]->args->number_of_coders;
	pthread_mutex_destroy(&coders[i]->args->stop_lock);
	pthread_mutex_destroy(coders[i]->args->print_lock);
	pthread_mutex_init(&coders[i]->args->mutex_time, NULL);
	pthread_cond_init(&coders[i]->args->cond_time, NULL);
	free(coders[i]->args->stop);
	free(coders[i]->args->print_lock);
	free(coders[i]->args);
	while (i < n_coder)
	{
		pthread_mutex_destroy(&coders[i]->right->lock);
		pthread_cond_destroy(&coders[i]->right->wait);
		pthread_mutex_destroy(&coders[i]->last_comp);
		free(coders[i]->right->queue->q);
		free(coders[i]->right->queue);
		free(coders[i]->right);
		free(coders[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_coder		**coders;
	t_arg		*args;
	t_dongle	**dongles;

	if (argc != 9)
		return (1);
	args = parsing(argc, argv);
	if (args == NULL)
		return (1);
	coders = malloc(sizeof(t_coder *) * args->number_of_coders);
	dongles = malloc(sizeof(t_dongle *) * args->number_of_coders);
	if (!coders || !dongles)
		return (1);
	init(coders, dongles, args);
	ft_creator(coders);
	ft_free(coders);
	free(dongles);
	free(coders);
	return (0);
}
