/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 03:39:01 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/21 11:23:13 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "coders.h"

int take_right_then_left(coder_t *coder, int *time1, int *time2)
{
        pthread_mutex_lock(&coder->right->lock);
        while (take_right(coder) == 0 && check_stop(coder, NULL) == 1)
            pthread_cond_wait(&coder->right->wait, &coder->right->lock);
        if(check_stop(coder, NULL) == 0)
            return (0);
        pthread_mutex_unlock(&coder->right->lock);
        *time1 = give_time() - coder->args->start;
        pthread_mutex_lock(&coder->left->lock);
        enqueue(coder->left->queue ,coder);
        while(take_left(coder) == 0 && check_stop(coder, NULL) == 1)
            pthread_cond_wait(&coder->left->wait, &coder->left->lock);
        if(check_stop(coder, NULL) == 0)
            return (0);
        pthread_mutex_unlock(&coder->left->lock);
        *time2 = give_time() - coder->args->start;
        if(check_stop(coder, NULL) == 0)
            return (0);
        return (1);
}

int take_left_then_right(coder_t *coder, int *time1, int *time2)
{
        pthread_mutex_lock(&coder->left->lock);
        while (take_left(coder) == 0 && check_stop(coder, NULL) == 1)
            pthread_cond_wait(&coder->left->wait, &coder->left->lock);
        if(check_stop(coder, NULL) == 0)
            return (0);
        pthread_mutex_unlock(&coder->left->lock);
        *time1 = give_time() - coder->args->start;
        pthread_mutex_lock(&coder->right->lock);
        enqueue(coder->right->queue ,coder);
        while (take_right(coder) == 0 && check_stop(coder, NULL) == 1)
            pthread_cond_wait(&coder->right->wait, &coder->right->lock);
        if(check_stop(coder, NULL) == 0)
            return (0);
        pthread_mutex_unlock(&coder->right->lock);
        *time2 = give_time() - coder->args->start;
        return (1);
}

int take_dongles(coder_t *coder, int *time1, int *time2)
{    
    if (coder->id % 2 == 0 )
    {
        if(take_right_then_left(coder, time1,time2) == 0)
            return (0);
    }
    else 
    {
        if(take_left_then_right(coder, time1,time2) == 0)
            return (0);
    }
    if(check_stop(coder, NULL) == 0)
        return (0);
    return (1);
}

int scheduler(coder_t *coder)
{
    int time1;
    int time2;

    time1 = 0;
    time2= 0;
    if(coder->id % 2 == 0)
    {
        pthread_mutex_lock(&coder->right->lock);
        enqueue(coder->right->queue ,coder);
        pthread_mutex_unlock(&coder->right->lock);
    }
    else
    {
        pthread_mutex_lock(&coder->left->lock);
        enqueue(coder->left->queue ,coder);
        pthread_mutex_unlock(&coder->left->lock);   
    }
    if (take_dongles(coder, &time1, &time2) == 0)
        return (0);
    pthread_mutex_lock(&coder->last_comp);
    coder->last_compile = give_time();
    pthread_mutex_unlock(&coder->last_comp);
    pthread_mutex_lock(coder->args->print_lock);
    printf("%d %d has taken a dongle\n",time1, coder->id);
    printf("%d %d has taken a dongle\n",time2, coder->id);
    pthread_mutex_unlock(coder->args->print_lock);

    return (1);
}