/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:58:43 by hrabh             #+#    #+#             */
/*   Updated: 2026/07/19 18:32:26 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

static void	monitor_helper(t_coder **coders, int i)
{
	int	j;

	j = 0;
	pthread_mutex_lock(&coders[i]->args->stop_lock);
	*coders[i]->args->stop = 0;
	pthread_mutex_unlock(&coders[i]->args->stop_lock);
	while (j < coders[0]->args->number_of_coders)
	{
		pthread_mutex_lock(&coders[j]->right->lock);
		pthread_cond_broadcast(&coders[j]->right->wait);
		pthread_mutex_unlock(&coders[j]->right->lock);
		pthread_mutex_lock(&coders[j]->left->lock);
		pthread_cond_broadcast(&coders[j]->left->wait);
		pthread_mutex_unlock(&coders[j]->left->lock);
		pthread_mutex_lock(&coders[j]->mutex_time);
		pthread_cond_broadcast(&coders[j]->cond_time);
		pthread_mutex_unlock(&coders[j]->mutex_time);
		j++;
	}
	usleep(1000);
	pthread_mutex_lock(coders[i]->args->print_lock);
	printf("%d ", (int)(give_time() - coders[i]->args->start));
	printf("%d burned out\n", coders[i]->id);
	pthread_mutex_unlock(coders[i]->args->print_lock);
}

static int	check_burnout(t_coder **coders, int i)
{
	long long	time;

	pthread_mutex_lock(&coders[i]->last_comp);
	time = coders[i]->last_compile + coders[i]->args->time_to_burnout;
	pthread_mutex_unlock(&coders[i]->last_comp);
	if (time < give_time())
	{
		monitor_helper(coders, i);
		return (1);
	}
	return (0);
}

void	*ft_monitor(void *arg)
{
	t_coder	**coders;
	int		i;

	coders = (t_coder **)arg;
	while (check_stop(coders[0]))
	{
		i = 0;
		while (i < coders[0]->args->number_of_coders)
		{
			if (check_burnout(coders, i) || !check_stop(coders[0]))
				return (NULL);
			if ((coders[0]->args->number_of_coders % 2 == 1)
				&& (coders[0]->args->dongle_cooldown
					+ coders[0]->args->time_to_compile)
				* 3 == coders[0]->args->time_to_burnout)
				usleep(1000);
			if ((coders[0]->args->number_of_coders % 2 == 0)
				&& (coders[0]->args->dongle_cooldown
					+ coders[0]->args->time_to_compile)
				* 2 == coders[0]->args->time_to_burnout)
				usleep(1000);
			i++;
		}
	}
	return (NULL);
}
