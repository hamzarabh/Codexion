/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 03:38:30 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/21 12:52:40 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

void	ft_swap(coder_t **n1, coder_t **n2)
{
	coder_t	*tmp;

	tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

long long	burntime(coder_t *coder)
{
	long long	time;

	pthread_mutex_lock(&coder->last_comp);
	time = coder->last_compile + coder->args->time_to_burnout;
	pthread_mutex_unlock(&coder->last_comp);
	return (time);
}

coder_t	**heapify(coder_t **tab, int size, int start)
{
	int		largest;
	int		left;
	int		right;

	left = start * 2 + 1;
	if (size == 1)
		return (tab);
	while ((left) < size)
	{
		left = start * 2 + 1;
		right = start * 2 + 2;
		largest = start;
		if (burntime(tab[left]) > burntime(tab[start]))
			largest = left;
		if (right < size && burntime(tab[right]) > burntime(tab[largest]))
			largest = right;
		if (largest != start)
		{
			ft_swap(&tab[largest], &tab[start]);
			start = largest;
		}
		else
			break ;
	}
	return (tab);
}

coder_t	**heap_sort(coder_t **arr, int size)
{
	int	i;

	if (size < 2)
		return (arr);
	i = (size / 2) - 1;
	while (i >= 0)
	{
		arr = heapify(arr, size, i);
		i--;
	}
	i = size - 1;
	while (i >= 0)
	{
		ft_swap(&arr[0], &arr[i]);
		arr = heapify(arr, i, 0);
		i--;
	}
	return (arr);
}
