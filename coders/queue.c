/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 03:39:46 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/20 03:39:47 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "coders.h"

void enqueue(Queue *q, coder_t *coder)
{
    if (q->count == q->size)
        return;
    q->q[q->count] = coder;
    q->count++;
}

coder_t * dequeue(Queue *q)
{
    coder_t *coder;

    if(q->count == 0)
        return (NULL);
    coder = q->q[0]; 

    if(q->count > 1)
        q->q[0] = q->q[1];
    else
        q->q[0] = NULL;

    q->count--;
    return (coder);
}