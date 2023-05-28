#include "philosophers.h"
long long get_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
void ft_usleep(long long time)
{
	long long start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}
void *monitor(void *arg);

void eat(t_philo *philo)
{
	// int  i = 0;
	

	printf("philosopher %d is eating\n",philo->id);
	printf("philosopher %d is full\n",philo->id);
	// pthread_mutex_lock(philo->last_meal_mutex);
	philo->last_meal = get_time();
	// printf("philosopher %d last meal %d\n",philo->id,philo->last_meal);
	// pthread_mutex_unlock(philo->last_meal_mutex);
	

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
	int right = philo->id % philo->nb_philo;
	if(philo->id % 2)
		usleep(100);
	while(1)
	{
		pthread_mutex_lock(&philo->forks[left]);
		printf("philosopher %d took a fork  \n",philo->id);
		pthread_mutex_lock(&philo->forks[right]);
		printf("philosopher %d took a fork\n",philo->id);
		eat(philo);
		ft_usleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->forks[left]);
		pthread_mutex_unlock(&philo->forks[right]);
		isa_sleep(philo);
		ft_usleep(philo->time_to_sleep);
		think(philo);
	}
	return NULL;
}

void *monitor(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;

	while(1)
	{

	int i  = 0;
		//check if dead
			// printf("diff %d\n",get_time() - philo->last_meal);
			// printf("time to die %d\n",philo->time_to_die);
			while(i < philo[i].nb_philo)
			{
				pthread_mutex_lock(philo[i].last_meal_mutex);
				if(get_time() - philo[i].last_meal > philo[i].time_to_die )
				{
					philo[i].state = DEAD;
					printf("philosopher %d died\n",philo[i].id);
					exit(0);
				}
				pthread_mutex_unlock(philo[i].last_meal_mutex);
			i++;
			}
			// pthread_mutex_unlock(philo->monitor);
	}
	return NULL;
}

void create_philosophers(t_philo *philo)
{
	int i = 0;
	pthread_t t[philo->nb_philo];
	pthread_t s;
	while(i < philo->nb_philo)
	{
		pthread_mutex_init(&philo->forks[i], NULL);
		philo[i].state = -1;
		philo[i].last_meal_mutex = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);

		pthread_mutex_init(&philo->last_meal_mutex[i], NULL);
		philo[i].id = i + 1;
		philo[i].forks = &philo->forks[i];
		philo[i].nb_philo = philo->nb_philo;
		philo[i].time_to_die = philo->time_to_die;
		philo[i].time_to_eat = philo->time_to_eat;
		philo[i].time_to_sleep = philo->time_to_sleep;
		philo[i].last_meal = get_time();
		pthread_create(&t[i], NULL, philosopher, &philo[i]);
		i++;
	}
	
	pthread_create(&s, NULL, monitor, philo); 
	i = 0;
	while(i < philo->nb_philo)
	{
		pthread_join(t[i], NULL);
		i++;
	}
		pthread_join(s, NULL);
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
	else if(ft_atoi(av[1]) < 1)
	{
		printf("wrong number of philosophers\n");
		return 1;
	}
	else if(ft_atoi(av[2]) < 60)
	{
		printf("wrong time to die\n");
		return 1;
	}
	else if(ft_atoi(av[3]) < 60)
	{
		printf("wrong time to eat\n");
		return 1;
	}
	else if(ft_atoi(av[4]) < 60)
	{
		printf("wrong time to sleep\n");
		return 1;
	}
	
	philo = malloc(sizeof(t_philo) * atoi(av[1]));
	philo->nb_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	philo->forks = malloc(sizeof(pthread_mutex_t) * philo->nb_philo);

	
	create_philosophers(philo); 
	i = 0;
	while(i < philo->nb_philo)
	{
		pthread_mutex_destroy(&philo->forks[i]);
		i++;
	}
	return 0;
}