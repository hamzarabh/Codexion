/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 10:41:43 by hrabh             #+#    #+#             */
/*   Updated: 2026/07/19 10:44:30 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

void	next_available(struct timespec *ts, long long available_at)
{
	ts->tv_sec = available_at / 1000;
	ts->tv_nsec = (available_at % 1000) * 1000000;
}

void	wait_dongle(t_dongle *dongle)
{
	struct timespec	ts;

	if (dongle->available_at != 0)
	{
		next_available(&ts, dongle->available_at);
		pthread_cond_timedwait(&dongle->wait, &dongle->lock, &ts);
	}
	else
		pthread_cond_wait(&dongle->wait, &dongle->lock);
}
