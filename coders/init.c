/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 03:38:14 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/21 13:34:44 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

static void	init_hlper(coder_t **coders, dongle **dongles, arg_t *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_coders)
	{
		dongles[i] = malloc(sizeof(dongle));
		coders[i] = malloc(sizeof(coder_t));
		dongles[i]->active = 1;
		dongles[i]->queue = malloc(sizeof(Queue));
		dongles[i]->queue->count = 0;
		dongles[i]->queue->size = 2;
		dongles[i]->queue->q = malloc(sizeof(coder_t *) * 2);
		coders[i]->args = args;
		coders[i]->id = i + 1;
		coders[i]->last_compile = args->start;
		coders[i]->right = dongles[i];
		if (i != 0)
			coders[i]->left = dongles[i - 1];
		coders[i]->last_compile = args->start;
		pthread_mutex_init(&coders[i]->last_comp, NULL);
		i++;
	}
	coders[0]->left = dongles[args->number_of_coders - 1];
}

void	init(coder_t **coders, dongle **dongles, arg_t *args)
{
	int	i;

	args->stop = malloc(sizeof(int));
	args->print_lock = malloc(sizeof(pthread_mutex_t));
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
