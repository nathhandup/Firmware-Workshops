#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* This implementation file is meant to showcase "race conditions" between threads. */
/* Our intention is to have each thread access a shared value , "shared", localize it as "x", */
/* and then do a comparison on "shared" and "x", then increment it at the end of the thread. */
/* We will observe that, although they are originally equal, when the comparison is made, */
/* they are no longer equal. This has to do with each thread incrementing this shared value, */
/* creating some weird results each time. */


void* run(void *arg) {

    /* Static variable foo which is shared between all threads */
    static int shared = 10;  

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

    return NULL;
}

/* Defining amount of threads we desire. */
#define THREAD_COUNT 5

int main(void) {
    /* Array of thread ID's */
    pthread_t t[THREAD_COUNT];

    /* Creating THREAD_COUNT amount of threads. */
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(t + i, NULL, run, NULL);
    }

    /* Joining all our threads and confirming they've terminated. */
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(t[i], NULL);
    }
}