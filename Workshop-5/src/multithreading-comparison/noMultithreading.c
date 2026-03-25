#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

/* This implementatino file is a little more complicated, but all we are doing is */
/* creating 3 arbitrary matrices, and performing a bunch of arbitrary computations. */
/* We create threads to deal with these computations, and time the process. */

/* This file is meant to be compared to multithreading.c, and observe how no multithreading */
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

/* performs some menial computation */
void computation (int x, int y);

int main (int argc, char **argv) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            computation(i, j);
        }
    }
	
	for (int i = 0; i < M; i++) { 
		for(int j = 0; j < N; j++)
		{ 
			printf("%d\t", SUMS[i][j]);
		}
		printf("\n");
	}

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("%ld.%09ld seconds elapsed.\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);
}

/* Deep insights: */
/* parallelism is not free. for small programs, sequential code */
/* is better. for large problems, threading wins */

void computation(int x, int y)
{	
    for(int i = 0; i < K; i++) {
        SUMS[x][y] += A[x][i] * B[i][y];
    }
}