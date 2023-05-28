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
	printf("philosopher %d is eating\n",philo->id);
	philo->last_meal = get_time();
	ft_usleep(philo->data.time_to_eat);
}
void think(t_philo *philo)
{
	printf("philosopher %d is thinking\n",philo->id);
}
void isa_sleep(t_philo *philo)
{
	printf("philosopher %d is sleeping\n",philo->id);
	ft_usleep(philo->data.time_to_sleep);
}
void *philosopher(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	int left;
	int right;

	left = philo->id - 1;
	right = philo->id % philo->data.nb_philo;
	if (philo->id % 2 == 0)
		usleep(100);
	while(1)
	{
		pthread_mutex_lock(&philo->data.forks[left]);
		printf("philosopher %d has taken a fork\n",philo->id);
		pthread_mutex_lock(&philo->data.forks[right]);
		printf("philosopher %d has taken a fork\n",philo->id);
		eat(philo);
		pthread_mutex_unlock(&philo->data.forks[left]);
		pthread_mutex_unlock(&philo->data.forks[right]);
		isa_sleep(philo);
		think(philo);
	}
	

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
			while(i < philo[i].data.nb_philo)
			{
				pthread_mutex_lock(philo[i].data.last_meal_mutex);
				if(get_time() - philo[i].last_meal > (size_t)philo[i].data.time_to_die )
				{
					// philo[i].state = DEAD;
					printf("philosopher %d died\n",philo[i].id);
					exit(0);
				}
				pthread_mutex_unlock(philo[i].data.last_meal_mutex);
			i++;
			}
			// pthread_mutex_unlock(philo->monitor);
	}
	return NULL;
}


t_data	*init_data(char **av)
{
	t_data *data;

	data = malloc(sizeof(t_data) * atoi(av[1]));
	data->nb_philo = atoi(av[1]);
	data->time_to_die = atoi(av[2]);
	data->time_to_eat = atoi(av[3]);
	data->time_to_sleep = atoi(av[4]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	data->last_meal_mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philo);

	int i = 0;
	while(i < data->nb_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->last_meal_mutex[i], NULL);
		i++;
	}
	
	return data;
	
}

t_philo *init_philo(t_data *data)
{
	t_philo *philo;
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	int i = 0;
	while(i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = get_time();
		philo[i].data = *data;
		i++;
	}

	return philo;


}


int main(int ac,char **av)
{
	
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



	t_philo *philo;
	t_data *data;

	data = init_data(av);
	philo = init_philo(data);

	
	while(i < data->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, philosopher, &philo[i]);
		i++;
	}
	pthread_create(&philo->monitor, NULL, monitor,philo);
	i = 0;

	while(i < data->nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	pthread_join(philo->monitor, NULL);
	

	
	return 0;
}

