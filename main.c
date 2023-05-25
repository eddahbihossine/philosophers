#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

		int mails ; 
		pthread_mutex_t mutex;
		int primes[10] =  {2, 3 , 4, 5, 6, 11 ,18 ,19, 44,29,23};
void* routine(void *arg)
{
	int index = *(int*)arg;
	printf("%d\n",primes[index]);
	free(arg);
}
void hi()
{
		system("leaks a.out");
}
int main()
{
		// atexit(hi);
		pthread_t   t[4];
		pthread_mutex_init(&mutex,NULL);
	int i  = 0;
	while (i < 4) 
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if(pthread_create(t + i,NULL,&routine,a) != 0)
		{
				perror("failed to create threads\n");
				return (1);
		}
		// printf("thread %d bda\n",i);
		i++;
	}
	for(i  = 0 ;i < 4;i++)
	{
		pthread_join(t[i],NULL);
		// printf("thread %d sala\n",i);
	}
	pthread_mutex_destroy(&mutex);
		// printf("%d\n",mails);
		return 0 ;
}
// sem_t room;
// sem_t chopstick[5];

// void * philosopher(void *);
// void eat(int);
// int main()
// {
// 	int i,a[5];
// 	pthread_t tid[5];
	
// 	sem_init(&room,0,4);
	
// 	for(i=0;i<5;i++)
// 		sem_init(&chopstick[i],0,1);
		
// 	for(i=0;i<5;i++){
// 		a[i]=i;
// 		pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);
// 	}
// 	for(i=0;i<5;i++)
// 		pthread_join(tid[i],NULL);
// }

// void * philosopher(void * num)
// {
// 	int phil=*(int *)num;

// 	sem_wait(&room);
// 	printf("\nPhilosopher %d has entered room",phil);
// 	sem_wait(&chopstick[phil]);
// 	sem_wait(&chopstick[(phil+1)%5]);

// 	eat(phil);
// 	sleep(2);
// 	printf("\nPhilosopher %d has finished eating",phil);

// 	sem_post(&chopstick[(phil+1)%5]);
// 	sem_post(&chopstick[phil]);
// 	sem_post(&room);
// }

// void eat(int phil)
// {
// 	printf("\nPhilosopher %d is eating",phil);
// }

