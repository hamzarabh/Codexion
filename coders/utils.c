/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:59:15 by hrabh             #+#    #+#             */
/*   Updated: 2026/06/20 20:59:33 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

long long	give_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000LL) + (now.tv_usec / 1000));
}

int	check_stop(t_coder *coder, pthread_t *ret)
{
	pthread_mutex_lock(&coder->args->stop_lock);
	if (*coder->args->stop == 0)
	{
		pthread_mutex_unlock(&coder->args->stop_lock);
		if (ret != NULL)
			pthread_join(*ret, NULL);
		return (0);
	}
	pthread_mutex_unlock(&coder->args->stop_lock);
	return (1);
}

void release_dongles(t_coder *coder)
{
    long long now;

    now = give_time();

    pthread_mutex_lock(&coder->right->lock);
    if (coder->args->dongle_cooldown == 0)
        coder->right->active = 1;
    else
        coder->right->available_at = now + coder->args->dongle_cooldown;
    pthread_cond_broadcast(&coder->right->wait);
    pthread_mutex_unlock(&coder->right->lock);

    pthread_mutex_lock(&coder->left->lock);
    if (coder->args->dongle_cooldown == 0)
        coder->left->active = 1;
    else
        coder->left->available_at = now + coder->args->dongle_cooldown;
    pthread_cond_broadcast(&coder->left->wait);
    pthread_mutex_unlock(&coder->left->lock);
}

int	take_right(t_coder *coder)
{
	if (strcmp(coder->args->scheduler, "edf") == 0)
		heap_sort(coder->right->queue->q, coder->right->queue->count);
	if (coder->right->queue->count > 0
    && coder->right->queue->q[0] == coder
    && coder->right->active == 0
    && coder->right->available_at != 0
    && give_time() >= coder->right->available_at)
{
    coder->right->active = 1;
    coder->right->available_at = 0;
}
	if (coder->right->active == 1)
	{
		if (coder == coder->right->queue->q[0])
		{
			coder->right->active = 0;
			dequeue(coder->right->queue);
			return (1);
		}
	}
	return (0);
}

int	take_left(t_coder *coder)
{
	if (strcmp(coder->args->scheduler, "edf") == 0)
		heap_sort(coder->left->queue->q, coder->left->queue->count);
	if (coder->left->queue->count > 0
    && coder->left->queue->q[0] == coder
    && coder->left->active == 0
    && coder->left->available_at != 0
    && give_time() >= coder->left->available_at)
{
    coder->left->active = 1;
    coder->left->available_at = 0;
}
	if (coder->left->active == 1)
	{
		if (coder == coder->left->queue->q[0])
		{
			coder->left->active = 0;
			dequeue(coder->left->queue);
			return (1);
		}
	}
	return (0);
}


