/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heddahbi <heddahbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:00:12 by heddahbi          #+#    #+#             */
/*   Updated: 2023/05/24 21:57:49 by heddahbi         ###   ########.fr       */
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


typedef struct s_philo
{
    time_t start;
    int nb_philo;
    int id;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    pthread_mutex_t *forks;
    
}           t_philo;
# endif
