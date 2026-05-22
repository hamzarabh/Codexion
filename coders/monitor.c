/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 03:38:40 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/22 11:22:23 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"




void monitor_helper(coder_t **coders, int i)
{
    int j;
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
        j++;
    }
    
    usleep(1000);
    pthread_mutex_lock(coders[i]->args->print_lock);
    printf("%d ",(int)(give_time() - coders[i]->args->start));
    printf("%d burned out\n", coders[i]-> id);
    pthread_mutex_unlock(coders[i]->args->print_lock);
}

void   *ft_monitor(void *arg)
{
    coder_t **coders;
    int     i;
    long long time;
    coders = (coder_t**)arg;
    while (check_stop(coders[0], NULL) == 0)
    {
        i = 0;
        while (i < coders[0]->args->number_of_coders)
        {
            pthread_mutex_lock(&coders[i]->last_comp);
            time = coders[i]->last_compile + coders[i]->args->time_to_burnout;
            pthread_mutex_unlock(&coders[i]->last_comp);
            if (time < give_time())
            {
                monitor_helper(coders, i);
                return (NULL);
            }
            if(check_stop(coders[0], NULL) == 0)
                return (0);
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}
