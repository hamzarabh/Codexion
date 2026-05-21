/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 03:38:40 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/20 04:38:59 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "coders.h"

void *ft_monitor(void *arg)
{
    coder_t **coders;
    int i;
    int j;
    long long time;
    coders = (coder_t**)arg;
    j = 0;
    while (1)
    {
        i = 0;
        while (i < coders[0]->args->number_of_coders)
        {
            pthread_mutex_lock(&coders[i]->last_comp);
            time = coders[i]->last_compile + coders[i]->args->time_to_burnout;
            pthread_mutex_unlock(&coders[i]->last_comp);
            if (time < give_time())
            {
                pthread_mutex_lock(&coders[i]->args->stop_lock);
                *coders[i]->args->stop = 0;
                pthread_mutex_unlock(&coders[i]->args->stop_lock); 
                while (j < coders[0]->args->number_of_coders)
                {
                    pthread_cond_broadcast(&coders[j]->right->wait);
                    pthread_cond_broadcast(&coders[j]->left->wait);
                    j++;
                }
                
                usleep(1000);
                pthread_mutex_lock(coders[i]->args->print_lock);
                printf("%d ",(int)(give_time() - coders[i]->args->start));
                printf("%d burned out\n", coders[i]-> id);
                pthread_mutex_unlock(coders[i]->args->print_lock);
                return (NULL);
            }
            pthread_mutex_lock(&coders[0]->args->stop_lock);
            if(*coders[0]->args->stop == 0)
            {
                pthread_mutex_unlock(&coders[0]->args->stop_lock);
                return (NULL);
            }
            pthread_mutex_unlock(&coders[0]->args->stop_lock);
            i++;
        }
        usleep(1000);
    }
}