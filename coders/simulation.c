/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:59:08 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/23 09:19:58 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

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
		usleep(coder->args->time_to_compile * 1000);
	else if (mode == 2)
		usleep(coder->args->time_to_debug * 1000);
	else if (mode == 3)
		usleep(coder->args->time_to_refactor * 1000);
}

void	*simulation(void *arg)
{
	t_coder		*coder;
	pthread_t	ret;
	int			i;

	i = -1;
	coder = (t_coder *) arg;
	while (++i < coder->args->number_of_compiles_required)
	{
		if (scheduler(coder) == 0)
			return (NULL);
		print_log(coder, 1);
		if (check_stop(coder, NULL) == 0)
			return (NULL);
		pthread_create(&ret, NULL, return_dongles, coder);
		if (check_stop(coder, &ret) == 0)
			return (NULL);
		print_log(coder, 2);
		if (check_stop(coder, &ret) == 0)
			return (NULL);
		print_log(coder, 3);
		pthread_join(ret, NULL);
		if (check_stop(coder, &ret) == 0)
			return (NULL);
	}
	return (NULL);
}
