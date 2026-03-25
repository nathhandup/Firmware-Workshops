#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* This implementation file is meant to showcase a solution to "raceConditions.c" */
/* in that we use a mutex, provided to us by pthread.h, to lock a shared variable until it is finished being used. */

pthread_mutex_t lock;

void* run(void *arg) {

    /* Static variable foo which is shared between all threads */
    static int shared = 10;  

    pthread_mutex_lock(&lock);

    /* Automatic local variable--each thread has its own */
    int x = shared; 

    /* We just assigned x from foo, so they'd better be equal here. */

    printf("Thread %d: x = %d, shared = %d\n", pthread_self(), x, shared);

    /* And they should be equal here, but they're not always! */

    /* What happens is another thread gets in and increments foo */
    /* right now, but this thread's x remains what it was before! */

    
    if (x != shared) {
        printf("Thread %d: Craziness! x != shared! %d != %d\n", pthread_self(), x, shared);
    }

    shared++;  // Increment shared value

    pthread_mutex_unlock(&lock);

    return NULL;
}

/* Defining amount of threads we desire. */
#define THREAD_COUNT 5

int main(void) {
    /* Array of thread ID's */
    pthread_t t[THREAD_COUNT];

    pthread_mutex_init(&lock, NULL);

    /* Creating THREAD_COUNT amount of threads. */
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(t + i, NULL, run, NULL);
    }

    /* Joining all our threads and confirming they've terminated. */
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(t[i], NULL);
    }

    pthread_mutex_destroy(&lock);
}