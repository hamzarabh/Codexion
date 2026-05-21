/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 10:11:00 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/21 11:14:53 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "coders.h"
long long	give_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000LL) + (now.tv_usec / 1000);
}


int	check_stop(coder_t *coder, pthread_t *ret)
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

void	*return_dongles(void *args)
{
	coder_t	*coder;

	coder = (coder_t *) args;
	usleep(coder->args->dongle_cooldown * 1000);
	pthread_mutex_lock(&coder->right->lock);
	coder->right->active = 1;
	pthread_cond_broadcast(&coder->right->wait);
	pthread_mutex_unlock(&coder->right->lock);
	pthread_mutex_lock(&coder->left->lock);
	coder->left->active = 1;
	pthread_cond_broadcast(&coder->left->wait);
	pthread_mutex_unlock(&coder->left->lock);
	return (NULL);
}
int take_right(coder_t *coder)
{
    if (strcmp(coder->args->scheduler, "edf")==0)
        heap_sort(coder->right->queue->q, coder->right->queue->count);
    if (coder->right->active == 1)
        if(coder == coder->right->queue->q[0])
        {
            coder->right->active = 0;
            dequeue(coder->right->queue);
            return (1);
        }
    return (0);
}

int take_left(coder_t *coder)
{
    if (strcmp(coder->args->scheduler, "edf")==0)
        heap_sort(coder->left->queue->q, coder->left->queue->count);
    if (coder->left->active == 1)
        if(coder == coder->left->queue->q[0])
        {
            coder->left->active = 0;
            dequeue(coder->left->queue);
            return (1);
        }
    return (0);
}