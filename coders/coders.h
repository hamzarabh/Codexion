/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:57:55 by hrabh             #+#    #+#             */
/*   Updated: 2026/06/19 10:59:16 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct t_arg	t_arg;
typedef struct t_queue	t_queue;

typedef struct t_dongle
{
	int				active;
	t_queue			*queue;
	pthread_mutex_t	lock;
	pthread_cond_t	wait;
}	t_dongle;

typedef struct t_coder
{
	int				id;
	long long		last_compile;
	t_dongle		*right;
	t_dongle		*left;
	t_arg			*args;
	pthread_mutex_t	last_comp;

}	t_coder;

typedef struct t_queue
{
	t_coder	**q;
	int		size;
	int		count;
}	t_queue;

typedef struct t_heap
{
	int	left;
	int	right;
}	t_heap;

typedef struct t_arg
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	char			*scheduler;
	long long		start;
	int				*stop;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	mutex_time;
	pthread_cond_t	cond_time;
	pthread_mutex_t	*print_lock;
}	t_arg;

t_arg		*parsing(int argc, char **argv);
void		*simulation(void *arg);
void		*ft_monitor(void *arg);
t_coder		**heap_sort(t_coder **arr, int size);
int			ft_creator(t_coder **coders);
void		init(t_coder **coders, t_dongle **dongles, t_arg *args);
int			scheduler(t_coder *coder);
void		enqueue(t_queue *q, t_coder *coder);
t_coder		*dequeue(t_queue *q);
int			check_stop(t_coder *coder, pthread_t *ret);
long long	give_time(void);
void		*return_dongles(void *args);
int			take_right(t_coder *coder);
int			take_left(t_coder *coder);
void		mysleep(int time, t_coder *coder);
#endif
