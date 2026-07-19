/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:59:08 by hrabh             #+#    #+#             */
/*   Updated: 2026/07/19 10:43:10 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

void	mysleep(int time, t_coder *coder)
{
	struct timespec	ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += time / 1000;
	ts.tv_nsec += (time % 1000) * 1000000L;
	if (ts.tv_nsec >= 1000000000L)
	{
		ts.tv_sec++;
		ts.tv_nsec -= 1000000000L;
	}
	pthread_mutex_lock(&coder->mutex_time);
	pthread_cond_timedwait(&coder->cond_time, &coder->mutex_time, &ts);
	pthread_mutex_unlock(&coder->mutex_time);
}

static void	print_log(t_coder *coder, int mode)
{
	long long	time;

	time = give_time() - coder->args->start;
	pthread_mutex_lock(coder->args->print_lock);
	if (mode == 1)
		printf("%lld %d is compiling\n", time, coder->id);
	else if (mode == 2)
		printf("%lld %d is debugging\n", time, coder->id);
	else
		printf("%lld %d is refactoring\n", time, coder->id);
	pthread_mutex_unlock(coder->args->print_lock);
	if (mode == 1)
		mysleep(coder->args->time_to_compile, coder);
	else if (mode == 2)
		mysleep(coder->args->time_to_debug, coder);
	else if (mode == 3)
		mysleep(coder->args->time_to_refactor, coder);
}

void	*simulation(void *arg)
{
	t_coder		*coder;
	int			i;

	i = -1;
	coder = (t_coder *)arg;
	while (++i < coder->args->number_of_compiles_required)
	{
		if (scheduler(coder) == 0)
			return (NULL);
		print_log(coder, 1);
		if (check_stop(coder, NULL) == 0)
			return (NULL);
		release_dongles(coder);
		if (check_stop(coder, NULL) == 0)
			return (NULL);
		print_log(coder, 2);
		if (check_stop(coder, NULL) == 0)
			return (NULL);
		print_log(coder, 3);
		if (check_stop(coder, NULL) == 0)
			return (NULL);
		usleep((coder->args->time_to_compile * 1000));
	}
	return (coder->last_compile = give_time() * 2, NULL);
}
