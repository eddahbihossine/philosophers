#include "philosophers.h"
void ft_usleep(int time)
{
	int i = 0;
	while(i < time)
	{
		usleep(1000);
		i++;
	}
}
void eat(t_philo *philo)
{
	printf("philosopher %d is eating\n",philo->id);
}
void think(t_philo *philo)
{
	printf("philosopher %d is thinking\n",philo->id);
}
void isa_sleep(t_philo *philo)
{
	printf("philosopher %d is sleeping\n",philo->id);
}
void *philosopher(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	int left = philo->id - 1;
	printf("left %d\n",left);
	// printf(" %d\n",philo->id % philo->nb_philo)
	int right = philo->id % philo->nb_philo;
	
	while(1)
	{
	// printf("r  ; %d\n",right);
	printf("l  ;%d\n",left);
		pthread_mutex_lock(&philo->forks[left]);
		printf("philosopher %d took a fork\n",philo->id);
		// pthread_mutex_lock(&philo->forks[right]);
		printf("philosopher %d took a fork\n",philo->id);
		eat(philo);
		pthread_mutex_unlock(&philo->forks[left]);
		pthread_mutex_unlock(&philo->forks[right]);
		isa_sleep(philo);
		think(philo);
		ft_usleep(10000);
		if(philo->nb_philo == 5)
			break;
	}
	return NULL;
}
// void *monitor(void *arg)
// {
// 	t_philo *philo;
// 	philo = (t_philo *)arg;
// 	while(1)
// 	{
// 		//check if dead
// 		if(philo->nb_philo == 0)
// 			break;
// 		if(philo->nb_philo == 1)
// 			break;
// 	}
// 	return NULL;
// }

void create_philosophers(t_philo *philo)
{
	int i = 0;
	pthread_t t[philo->nb_philo];
	while(i < philo->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].forks = philo->forks;
		philo[i].nb_philo = philo->nb_philo;
		pthread_create(&t[i], NULL, philosopher, &philo[i]);
		i++;
	}

	i = 0;
	while(i < philo->nb_philo)
	{
		pthread_join(t[i], NULL);
		i++;
	}
}
int main(int ac,char **av)
{
	t_philo *philo;
	(void)ac;
	int i = 0;
	if(ac != 5)
	{
		printf("wrong number of arguments\n");
		return 1;
	}
	philo = malloc(sizeof(t_philo) * atoi(av[1]));
	philo->nb_philo = atoi(av[1]);
	philo->time_to_die = atoi(av[2]);
	philo->time_to_eat = atoi(av[3]);
	philo->time_to_sleep = atoi(av[4]);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);
	while(i < philo->nb_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		i++;
	}
	create_philosophers(philo); 
	i = 0;
	while(i < philo->nb_philo)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	return 0;
}