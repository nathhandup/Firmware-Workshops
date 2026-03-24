#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* run(void *arg) {
    int i = *(int*)arg;  // Copy the arg

    free(arg);  // Done with this

    printf("THREAD %d: running!\n", i);

    return NULL;
}

#define THREAD_COUNT 5

int main(void) {
    pthread_t t[THREAD_COUNT];

    int i;

    printf("Launching threads...\n");
    for (i = 0; i < THREAD_COUNT; i++) {
        // Get some space for a per-thread argument:

        int *arg = malloc(sizeof *arg);
        *arg = i;

        pthread_create(t + i, NULL, run, (void *)arg);
    }
    for (i = 0; i < THREAD_COUNT; i++) {
        pthread_join(t[i], NULL);
        printf("Thread %d complete!\n", i);
    }
}
