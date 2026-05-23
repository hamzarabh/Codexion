/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 18:58:09 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/22 18:58:11 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

static void	ft_swap(t_coder **n1, t_coder **n2)
{
	t_coder	*tmp;

	tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

static long long	burntime(t_coder *coder)
{
	long long	time;

	pthread_mutex_lock(&coder->last_comp);
	time = coder->last_compile + coder->args->time_to_burnout;
	pthread_mutex_unlock(&coder->last_comp);
	return (time);
}

static t_coder	**heapify(t_coder **tab, int size, int start)
{
	int	largest;
	int	left;
	int	right;

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

t_coder	**heap_sort(t_coder **arr, int size)
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
