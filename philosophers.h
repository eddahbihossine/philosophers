/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:00:12 by heddahbi          #+#    #+#             */
/*   Updated: 2023/05/29 00:30:16 by heddahbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# define EAT 0
# define SLEEP 1
# define THINK 2
# define DEAD 3
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>


typedef struct s_data
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    pthread_mutex_t *forks;
    pthread_mutex_t *last_meal_mutex;
    int state;
    
}           t_data;
typedef struct s_philo
{
    pthread_t thread;
    pthread_t monitor;
    int id;
    size_t last_meal;
    t_data data;
} t_philo;

int	ft_atoi(char *str); 

# endif
