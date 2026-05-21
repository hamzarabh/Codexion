/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrabh <hrabh@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 03:39:15 by hrabh             #+#    #+#             */
/*   Updated: 2026/05/21 11:15:20 by hrabh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CODERS_H
#define CODERS_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>


typedef struct  arg_t arg_t;
typedef struct Queue Queue;

typedef struct dongle{
    int active;
    Queue *queue;
    pthread_mutex_t lock;
    pthread_cond_t wait;
}dongle;

typedef struct coder_t{
    int id;
    int *stop;
    long long last_compile;
    struct coder_t *coders;
    dongle *right;
    dongle *left;
    arg_t *args;
   // pthread_cond_t *wait;
    pthread_mutex_t last_comp;
    
}coder_t;

typedef struct Queue
{
    coder_t **q;
    int size;
  //  int front;
   // int rear;
    int count;
}Queue;


typedef struct  arg_t
{
    int number_of_coders;
    int time_to_burnout;
    int time_to_compile;
    int time_to_debug;
    int time_to_refactor;
    int number_of_compiles_required;
    int dongle_cooldown;
    char *scheduler;
    long long start;
    int *stop;
    //pthread_mutex_t lock;
   // pthread_cond_t dong_wait;
    pthread_mutex_t stop_lock;
    pthread_mutex_t *print_lock;
}arg_t;

arg_t *parsing(int argc, char **argv);
void *simulation(void *arg);
void *ft_monitor(void *arg);
coder_t **heap_sort(coder_t **arr,int size);
int	ft_creator(coder_t **coders);
void	init(coder_t **coders, dongle **dongles, arg_t *args);
int scheduler(coder_t *coder);
void enqueue(Queue *q, coder_t *coder);
coder_t * dequeue(Queue *q);
int	check_stop(coder_t *coder, pthread_t *ret);
long long	give_time(void);
void	*return_dongles(void *args);
int take_right(coder_t *coder);
int take_left(coder_t *coder);
#endif