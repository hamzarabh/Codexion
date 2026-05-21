#include "coders.h"

void	print_log(coder_t *coder, int mode)
{
	pthread_mutex_lock(coder->args->print_lock);
	if (mode == 1)
		printf("%lld %d is compiling\n", give_time() - coder->args->start, coder->id);
	else if (mode == 2)
		printf("%lld %d is debugging\n", give_time() - coder->args->start, coder->id);
	else
		printf("%lld %d is refactoring\n", give_time() - coder->args->start, coder->id);
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
	coder_t		*coder;
	pthread_t	ret;
	int			next;
	int			i;

	i = 0;
	coder = (coder_t *) arg;
	while (i < coder->args->number_of_compiles_required)
	{
		scheduler(coder);
		if (check_stop(coder, NULL) == 0)
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
		i++;
	}
	return (NULL);
}