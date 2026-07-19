/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:59:01 by hrabh             #+#    #+#             */
/*   Updated: 2026/06/20 20:40:08 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

static int	take_right_then_left(t_coder *coder)
{
	pthread_mutex_lock(&coder->right->lock);
	while (take_right(coder) == 0 && check_stop(coder, NULL) == 1)
		wait_dongle(coder->right);
	pthread_mutex_unlock(&coder->right->lock);
	pthread_mutex_lock(&coder->left->lock);
	enqueue(coder->left->queue, coder);
	while (take_left(coder) == 0 && check_stop(coder, NULL) == 1)
		wait_dongle(coder->left);
	pthread_mutex_unlock(&coder->left->lock);
	if (check_stop(coder, NULL) == 0)
		return (0);
	return (1);
}

static int	take_left_then_right(t_coder *coder)
{
	pthread_mutex_lock(&coder->left->lock);
	while (take_left(coder) == 0 && check_stop(coder, NULL) == 1)
		wait_dongle(coder->left);
	pthread_mutex_unlock(&coder->left->lock);
	pthread_mutex_lock(&coder->right->lock);
	enqueue(coder->right->queue, coder);
	while (take_right(coder) == 0 && check_stop(coder, NULL) == 1)
		wait_dongle(coder->right);
	pthread_mutex_unlock(&coder->right->lock);
	return (1);
}

static int	take_dongles(t_coder *coder)
{
	if (coder->id % 2 == 0)
	{
		if (take_right_then_left(coder) == 0)
			return (0);
	}
	else
	{
		if (take_left_then_right(coder) == 0)
			return (0);
	}
	if (check_stop(coder, NULL) == 0)
		return (0);
	return (1);
}

static void	helper_scheduler(t_coder *coder)
{
	long long	time;

	pthread_mutex_lock(&coder->last_comp);
	coder->last_compile = give_time();
	pthread_mutex_unlock(&coder->last_comp);
	pthread_mutex_lock(coder->args->print_lock);
	time = give_time() - coder->args->start;
	printf("%lld %d has taken a dongle\n", time, coder->id);
	printf("%lld %d has taken a dongle\n", time, coder->id);
	pthread_mutex_unlock(coder->args->print_lock);
}

int	scheduler(t_coder *coder)
{
	if (coder->id % 2 == 0)
	{
		pthread_mutex_lock(&coder->right->lock);
		enqueue(coder->right->queue, coder);
		pthread_mutex_unlock(&coder->right->lock);
	}
	else
	{
		pthread_mutex_lock(&coder->left->lock);
		enqueue(coder->left->queue, coder);
		pthread_mutex_unlock(&coder->left->lock);
	}
	if (take_dongles(coder) == 0)
		return (0);
	helper_scheduler(coder);
	if (check_stop(coder, NULL) == 0)
		return (0);
	return (1);
}
