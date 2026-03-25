#include <stdio.h>
#include <pthread.h>

/* This example shows more on race conditions, in that each thread is looking */
/* At the same pointer to a shared value "i", and some weird things happen when each */
/* thread dereferences it's passed value, since it's been incremented in the main thread. */

/* Key question: what ways can we solve this? */

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

    /* Creating our threads */
    printf("Launching threads...\n");
    for (i = 0; i < THREAD_COUNT; i++) {
        /* NOTE! */
        /* In the following line, we pass a pointer to i */
        /* but each thread sees the same pointer. So they'll */
        /* print out weird things as i changes value here in */
        /* the main thread! */
        pthread_create(t + i, NULL, run, &i);
    }

    /* Doing some stuff.. */
    printf("Doing other things while the thread runs...\n");
    printf("Waiting for thread to complete...\n");

    /* Join all of our threads and state that they are complete when they are. */
    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(t[i], NULL);

        printf("Thread %d complete!\n", i);
    }

    printf("All threads complete!\n");
}