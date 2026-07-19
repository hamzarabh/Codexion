/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:58:55 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/22 18:58:58 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

void	enqueue(t_queue *q, t_coder *coder)
{
	if (q->count == q->size)
		return ;
	q->q[q->count] = coder;
	q->count++;

}

t_coder	*dequeue(t_queue *q)
{
	t_coder	*coder;

	if (q->count == 0)
		return (NULL);
	coder = q->q[0];
	
	if (q->count > 1)
	{
		q->q[0] = q->q[1];
		q->q[1] = NULL;
	}
	else
	{
		q->q[0] = NULL;
	}
	q->count--;
	return (coder);
}