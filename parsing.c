/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 03:38:24 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/20 03:38:25 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



# include "coders.h"

void helper(arg_t *argument,int index, int num)
{
    if (index == 1)
        argument->number_of_coders = num;
    if (index == 2)
        argument->time_to_burnout = num;
    if (index == 3)
        argument->time_to_compile = num;
    if (index == 4)
        argument->time_to_debug = num;
    if (index == 5)
        argument->time_to_refactor = num;
    if (index == 6)
        argument->number_of_compiles_required = num;
    if (index == 7)
        argument->dongle_cooldown = num;
}


void *check_scheduler(arg_t *argument, char *scheduler)
{
    if (strcmp(scheduler,"fifo") == 0)
        argument->scheduler = scheduler;
    else if(strcmp(scheduler,"edf") == 0)
        argument->scheduler = scheduler;
    else
        return (NULL);
}


arg_t *parsing(int argc, char **argv)
{
    int i;
    arg_t *argument;
    int num;
    if (argc !=  9)
        return (NULL);
    argument = malloc(sizeof(arg_t));
    i = 1;
    while (i < argc -1)
    {
        num = atoi(argv[i]);
        if(num != 0)
        {
            if (num < 0)
                return (NULL);
            helper(argument, i,num);
        }
        else
            return (NULL);
        i++;
    }
    if (check_scheduler(argument, argv[i]) == NULL)
        return (NULL);
    return (argument);   
}