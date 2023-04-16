#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *thread(void *arg)
{
    int threadId = *(int *)arg;
    printf("hello from thread id: %d \n", threadId);
    pthread_exit(NULL);
}

int main()
{
    int N = 5;
    pthread_t threads[N];
    int threadArgs[N];

    for (int i = 0; i < N; i++)
    {
        threadArgs[i] = i + 1;
        int result = pthread_create(&threads[i], NULL, thread, threadArgs + i);
        if (result != 0)
        {
            printf("Failed to create thread\n");
            exit(1);
        }
        printf("Thread created: %d\n", i + 1);
        sleep(10);
    }

    // wait for all threads to finish
    for (int i = 0; i < N; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
