#include <stdio.h>
#include <pthread.h>

void* run(void *arg)
{
    int i = *(int*)arg;

    printf("THREAD %d: running!\n", i);

    return NULL;
}

#define THREAD_COUNT 5

int main(void)
{
    pthread_t t[THREAD_COUNT];

    int i;

    printf("Launching threads...\n");
    for (i = 0; i < THREAD_COUNT; i++)

        // NOTE! In the following line, we pass a pointer to i, 
        // but each thread sees the same pointer. So they'll
        // print out weird things as i changes value here in
        // the main thread!

        pthread_create(t + i, NULL, run, &i);

    printf("Doing other things while the thread runs...\n");
    printf("Waiting for thread to complete...\n");

    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(t[i], NULL);

        printf("Thread %d complete!\n", i);
    }

    printf("All threads complete!\n");
}