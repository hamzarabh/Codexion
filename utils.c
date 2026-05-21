#include "coders.h"
#include <sys/time.h>
long long	give_time(void)
{
	// long long time ;
	struct timeval	now;

	gettimeofday(&now, NULL);
	// time = ((now.tv_usec )/1000 )+  ((now.tv_sec ) * 1000);
	return (now.tv_sec * 1000LL) + (now.tv_usec / 1000);
}
int	check_stop(coder_t *coder, pthread_t *ret)
{
	pthread_mutex_lock(&coder->args->stop_lock);
	if (*coder->args->stop == 0)
	{
		pthread_mutex_unlock(&coder->args->stop_lock);
		if (ret != NULL)
			pthread_join(*ret, NULL);
		return (0);
	}
	pthread_mutex_unlock(&coder->args->stop_lock);
	return (1);
}

void	*return_dongles(void *args)
{
	coder_t	*coder;
	int		id;
	int		next;

	coder = (coder_t *) args;
	usleep(coder->args->dongle_cooldown * 1000);
	pthread_mutex_lock(&coder->right->lock);
	coder->right->active = 1;
	pthread_cond_broadcast(&coder->right->wait);
	pthread_mutex_unlock(&coder->right->lock);
	pthread_mutex_lock(&coder->left->lock);
	coder->left->active = 1;
	pthread_cond_broadcast(&coder->left->wait);
	pthread_mutex_unlock(&coder->left->lock);
	return (NULL);
}