#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/* This implementatino file is a little more complicated, but all we are doing is */
/* creating 3 arbitrary matrices, and performing a bunch of arbitrary computations. */
/* We create threads to deal with these computations, and time the process. */

/* This file is meant to be compared to noMultithreading.c, and observe how no multithreading */
/* is faster. */

/* parallelism is not free. there is overhead. For small programs, 
/* sequential code is better. for large problems, threading wins. */


#define M 3
#define K 3
#define N 3
#define NUM_THREADS M * N

/* Global variables for threads to share */
int A[M][K] = {{1, 4, 5}, 
               {2, 5, 3}, 
               {3, 6, 2}};
int B[K][N] = {{8, 7, 6}, 
               {5, 4, 3}, 
               {2, 3, 6}};
/* To store sums */
int SUMS[M][N];

/* Structure for passing data to threads */
/* Contains a row # and column # */
struct v {
	int i; /* row */
	int j; /* column */
};

/* the thread function*/
void *runner (void *ptr); 

int main (int argc, char **argv) {
    /* Time storing */
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

	int thread_counter = 0;
	
	pthread_t workers[NUM_THREADS];
	
	/* We have to create M * N worker threads */
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			struct v *data = (struct v *) malloc(sizeof(struct v));
			data->i = i;
			data->j = j;
			/* Now we will create the thread passing it data as a paramater*/
			pthread_create(&workers[thread_counter], NULL, runner, data);
			thread_counter++;
		}
	}
	
	/* Waiting for threads to complete */
	for (int i = 0; i < NUM_THREADS; i++) {
	    pthread_join(workers[i], NULL);
	}
	
    /* Printing our SUMS matrix */
	for (int i = 0; i < M; i++) { 
		for(int j = 0; j < N; j++)
		{ 
			printf("%d\t", SUMS[i][j]);
		}
		printf("\n");
	}

    /* Printing time */
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("%ld.%09ld seconds elapsed.\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);
}

void *runner(void *ptr)
{	
	/* Casting paramater to struct v pointer */
	struct v *data = ptr;
	int sum = 0;
	
    /* Arbitrary computations */
	for(int i = 0; i < K; i++)
	{	
		sum += A[data->i][i] * B[i][data->j];
	}
	
	SUMS[data->i][data->j] = sum;
	pthread_exit(NULL);
}