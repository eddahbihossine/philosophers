
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
	printf("%lld %d is eating 🍲 \n",get_time() - philo->nb, philo->id);
	philo->last_meal = get_time();
	ft_usleep(philo->data.time_to_eat);
}
void think(t_philo *philo)
{
	printf("%lld %d is thinking 🤔\n",get_time() - philo->nb, philo->id);
}
void isa_sleep(t_philo *philo)
{
	printf("%lld %d is sleeping 💤 \n",get_time() - philo->nb, philo->id);
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
		printf("%lld %d has taken a fork 🍴 \n",get_time() - philo->nb, philo->id);
		pthread_mutex_lock(&philo->data.forks[right]);
		printf("%lld %d has taken a fork 🍴 \n",get_time() - philo->nb, philo->id);
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
			while(i < philo[i].data.nb_philo)
			{
				pthread_mutex_lock(philo[i].data.last_meal_mutex);
				if(get_time() - philo[i].last_meal > (size_t)philo[i].data.time_to_die )
				{
					printf("%lld %d died 💀\n", get_time() - philo->nb,philo[i].id);
					return NULL;
				}
				pthread_mutex_unlock(philo[i].data.last_meal_mutex);
			i++;
		}
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
	data->nb_eat = atoi(av[5]);
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
		philo[i].nb = get_time();
		philo[i].data = *data;
		i++;
	}

	return philo;

}
void free_data(t_data *data)
{
	int i = 0;
	while(i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->last_meal_mutex[i]);
		i++;
	}
	free(data->forks);
	free(data->last_meal_mutex);
	free(data);
}
void free_philo(t_philo *philo)
{
	free(philo);
}
int parse(int ac , char **av)
{
	if(ac != 5)
		printf("wrong number of arguments\n");
	else if(ft_atoi(av[1]) < 1)
		printf("wrong number of philosophers\n");
	else if(ft_atoi(av[2]) < 60)
		printf("wrong time to die\n");
	
	else if(ft_atoi(av[3]) < 60)
		printf("wrong time to eat\n");
		
	else if(ft_atoi(av[4]) < 60)
		printf("wrong time to sleep\n");
	else
	   return 0;
	return 1;
}

int main(int ac,char **av)
{

	if(parse(ac,av))
		return 1;
	t_philo *philo;
	t_data *data;

	data = init_data(av);
	philo = init_philo(data);
	int i = 0;
	while(i < data->nb_philo)
	{
		pthread_create(&philo[i].thread, NULL, philosopher, &philo[i]);
		pthread_detach(philo[i].thread);
		i++;
	}
	pthread_create(&philo->monitor, NULL, monitor,philo);
	pthread_join(philo->monitor, NULL);
	free_data(data);

	return(0);
}
