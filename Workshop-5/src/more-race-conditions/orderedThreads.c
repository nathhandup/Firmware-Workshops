#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Related to our "jumbledThreads.c", this is a potential solution to our */
/* jumbled threads problem. Instead of having them all read from the exact same */
/* stack pointer, we will simply allocate a pointer for each thread so there are */
/* no conflicts! */

void* run(void *arg) {
    /* Casting, dereferencing and storing in i */
    int i = *(int*)arg;  // Copy the arg
    /* Done with our malloc'd memory, free it */
    free(arg);  

    printf("THREAD %d: running!\n", i);

    return NULL;
}

#define THREAD_COUNT 5

int main(void) {
    /* Array of thread ID's */
    pthread_t t[THREAD_COUNT];

    int i;

    /* Creating all of our threads */
    printf("Launching threads...\n");
    for (i = 0; i < THREAD_COUNT; i++) {
        /* Allocating space to store the current i value */
        int *arg = (int *)malloc(sizeof *arg);
        *arg = i;

        /* Create thread, pass it our malloc'd value as an argument. */
        pthread_create(t + i, NULL, run, (void *)arg);
    }

    /* Join all of our threads to our main thread */
    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(t[i], NULL);
        printf("Thread %d complete!\n", i);
    }
}
