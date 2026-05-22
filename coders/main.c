/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 03:40:04 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/21 13:38:06 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

void	ft_free(coder_t **coders)
{
	int	n_coder;
	int	i;

	i = 0;
	n_coder = coders[0]->args->number_of_coders;
	pthread_mutex_destroy(&coders[i]->args->stop_lock);
	pthread_mutex_destroy(coders[i]->args->print_lock);
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
	coder_t	**coders;
	arg_t	*args;
	dongle	**dongles;

	args = parsing(argc, argv);
	if (args == NULL)
		return (1);
	coders = malloc(sizeof(coder_t *) * args->number_of_coders);
	dongles = malloc(sizeof(dongle *) * args->number_of_coders);
	init(coders, dongles, args);
	ft_creator(coders);
	ft_free(coders);
	free(dongles);
	free(coders);
	return (0);
}
