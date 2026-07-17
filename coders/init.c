/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:58:19 by hrabh             #+#    #+#             */
/*   Updated: 2026/06/20 20:22:21 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

static void	init_hlper(t_coder **coders, t_dongle **dongles, t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_coders)
	{
		dongles[i] = malloc(sizeof(t_dongle));
		coders[i] = malloc(sizeof(t_coder));
		dongles[i]->active = 1;
		dongles[i]->available_at = 0;
		dongles[i]->queue = malloc(sizeof(t_queue));
		dongles[i]->queue->count = 0;
		dongles[i]->queue->size = 2;
		dongles[i]->queue->q = malloc(sizeof(t_coder *) * 2);
		coders[i]->args = args;
		coders[i]->id = i + 1;
		coders[i]->last_compile = args->start;
		coders[i]->right = dongles[i];
		if (i != 0)
			coders[i]->left = dongles[i - 1];
		pthread_mutex_init(&coders[i]->last_comp, NULL);
		pthread_mutex_init(&coders[i]->mutex_time, NULL);
		pthread_cond_init(&coders[i]->cond_time, NULL);
		i++;
	}
	coders[0]->left = dongles[args->number_of_coders - 1];
}

void	init(t_coder **coders, t_dongle **dongles, t_arg *args)
{
	int	i;

	args->stop = malloc(sizeof(int));
	args->print_lock = malloc(sizeof(pthread_mutex_t));
	if (!args->stop || !args->print_lock)
		return ;
	pthread_mutex_init(&args->stop_lock, NULL);
	pthread_mutex_init(args->print_lock, NULL);

	*args->stop = 1;
	args->start = give_time();
	init_hlper(coders, dongles, args);
	i = 0;
	while (i < args->number_of_coders)
	{
		pthread_mutex_init(&dongles[i]->lock, NULL);
		pthread_cond_init(&dongles[i]->wait, NULL);
		i++;
	}
}
