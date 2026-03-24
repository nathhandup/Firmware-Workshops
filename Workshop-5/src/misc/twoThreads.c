#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_t thread;
pthread_t thread2;

void* myThreadFunction(void* arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    /* Will be next cancelled at a cancellation point */
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL); 
    pthread_t thisThread = pthread_self();
    while(1) {
        printf("Current Running Thread: %lu\n", (unsigned long)thisThread);
        pthread_testcancel(); 
        sleep(1);
    }
    return NULL;
}

void* myThreadFunction2(void* arg) {
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    /* Will be next cancelled at a cancellation point */
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL); 
    pthread_t thisThread = pthread_self();
    while(1) {
        printf("Current Running Thread: %lu\n", (unsigned long)thisThread);
        pthread_testcancel(); 
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_create(&thread, NULL, myThreadFunction, NULL);
    pthread_create(&thread2, NULL, myThreadFunction2, NULL);
    sleep(5); // doing stuff..
    pthread_cancel(thread);
    pthread_cancel(thread2);
    pthread_join(thread, NULL);
    pthread_join(thread2, NULL);
    printf("Main thread finished.\n");
}