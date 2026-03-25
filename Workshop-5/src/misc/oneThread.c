#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/* This is a basic implementation file showcasing basic creation of threads. */
/* Getting familiar with our thread creation, and observing how the order */
/* in the console is slightly jumbled. */

void* myThreadFunction(void* arg) {
    pthread_t thisThread = pthread_self();
    while(1) {
        printf("Current Running Thread: %lu\n", (unsigned long)thisThread);
        pthread_testcancel(); // creating a cancellation point 
        sleep(1);
    }
    return NULL;
}

pthread_t thread;

int main() {
    /* Create our two thread. */
    /* ARGS: 
    /* Pointer to pthread_t, config (NULL for default),  a function, and argument passed */
    pthread_create(&thread, NULL, myThreadFunction, NULL);

    sleep(5); // doing stuff..

    /* Cancel our thread */
    pthread_cancel(thread);

    /* Wait for them to fully clean */
    /* Basically joining them with our "main" thread */
    pthread_join(thread, NULL);

    printf("Main thread finished.\n");
}