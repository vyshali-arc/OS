#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

int state[N]; // 0=thinking, 1=hungry, 2=eating
pthread_mutex_t mutex;
pthread_cond_t cond[N];

void test(int i)
{
    if(state[i] == 1 &&
       state[(i+4)%N] != 2 &&
       state[(i+1)%N] != 2)
    {
        state[i] = 2;
        printf("Philosopher %d is Eating\n", i);
        pthread_cond_signal(&cond[i]);
    }
}

void take_fork(int i)
{
    pthread_mutex_lock(&mutex);

    state[i] = 1;
    printf("Philosopher %d is Hungry\n", i);

    test(i);

    while(state[i] != 2)
        pthread_cond_wait(&cond[i], &mutex);

    pthread_mutex_unlock(&mutex);
}

void put_fork(int i)
{
    pthread_mutex_lock(&mutex);

    state[i] = 0;
    printf("Philosopher %d is Thinking\n", i);

    test((i+4)%N);
    test((i+1)%N);

    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* num)
{
    int i = *(int*)num;

    while(1)
    {
        sleep(1);
        take_fork(i);
        sleep(1);
        put_fork(i);
    }
}

int main()
{
    int i;
    pthread_t thread[N];
    int phil[N];

    pthread_mutex_init(&mutex, NULL);

    for(i = 0; i < N; i++)
        pthread_cond_init(&cond[i], NULL);

    for(i = 0; i < N; i++)
    {
        phil[i] = i;
        pthread_create(&thread[i], NULL, philosopher, &phil[i]);
    }

    for(i = 0; i < N; i++)
        pthread_join(thread[i], NULL);

    return 0;
}
