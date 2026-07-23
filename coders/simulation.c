/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:59:08 by hrabh             #+#    #+#             */
/*   Updated: 2026/07/19 18:34:40 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

void	mysleep(int time, t_coder *coder)
{
	struct timespec	ts;
	int				stop;

	stop = 1;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += time / 1000;
	ts.tv_nsec += (time % 1000) * 1000000L;
	if (ts.tv_nsec >= 1000000000L)
	{
		ts.tv_sec++;
		ts.tv_nsec -= 1000000000L;
	}
	pthread_mutex_lock(&coder->mutex_time);
	while (stop)
	{
		stop = 0;
		pthread_cond_timedwait(&coder->cond_time, &coder->mutex_time, &ts);
	}
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

static void	odd_delay(t_coder *coder)
{
	long	max_time;

	max_time = coder->args->time_to_compile + coder->args->time_to_debug
		+ coder->args->time_to_refactor;
	if (coder->args->number_of_coders % 2 == 0)
		return ;
	if (max_time <= coder->args->dongle_cooldown)
	{
		if (max_time + (coder->args->dongle_cooldown
				* 2) < coder->args->time_to_burnout)
			mysleep(coder->args->dongle_cooldown * 2, coder);
	}
	else
	{
		if (max_time + coder->args->time_to_compile
			+ coder->args->dongle_cooldown < coder->args->time_to_burnout)
		{
			mysleep((coder->args->time_to_compile
					+ coder->args->dongle_cooldown), coder);
		}
	}
}

static int	compile_cycle(t_coder *coder, int is_last)
{
	if (scheduler(coder) == 0 || check_stop(coder) == 0)
		return (0);
	print_log(coder, 1);
	if (check_stop(coder) == 0)
		return (0);
	release_dongles(coder);
	if (check_stop(coder) == 0)
		return (0);
	print_log(coder, 2);
	if (check_stop(coder) == 0)
		return (0);
	print_log(coder, 3);
	if (check_stop(coder) == 0)
		return (0);
	if (!is_last)
		odd_delay(coder);
	return (1);
}

void	*simulation(void *arg)
{
	t_coder	*coder;
	int		i;
	int		max;

	coder = (t_coder *)arg;
	max = coder->args->number_of_compiles_required;
	i = -1;
	while (++i < max)
	{
		if (compile_cycle(coder, i == max - 1) == 0)
			return (NULL);
	}
	pthread_mutex_lock(&coder->last_comp);
	coder->last_compile = give_time() * 2;
	pthread_mutex_unlock(&coder->last_comp);
	return (NULL);
}
