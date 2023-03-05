#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define ARRAY_SIZE 200000000

// Forward declarations.
//
void setup_data(int *a, int *b);
void do_addition(int *a, int *b, int *sum);

int main(int argc, char** argv) {
    int *a   = malloc(ARRAY_SIZE * sizeof(*a));
    int *b   = malloc(ARRAY_SIZE * sizeof(*b));
    int *sum = malloc(ARRAY_SIZE * sizeof(*sum));

    if (a == NULL || b == NULL || sum == NULL) {
        fprintf(stderr, "Unable to allocate memory.\n");
	return -1;
    }

    setup_data(a, b);
    struct timespec start_time;
    struct timespec end_time;
    int retval;
    retval = clock_gettime(CLOCK_MONOTONIC, &start_time);
    if (retval == -1) {
        fprintf(stderr, "clock_gettime() for start time failed.\n");
    }
    do_addition(a, b, sum);
    retval = clock_gettime(CLOCK_MONOTONIC, &end_time);
    if (retval == -1) {
        fprintf(stderr, "clock_gettime() for start time failed.\n");
    }
    long elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000000000;
    if (start_time.tv_nsec > end_time.tv_nsec) {
        elapsed_time += end_time.tv_nsec - start_time.tv_nsec;
    } else {
        elapsed_time += end_time.tv_nsec - start_time.tv_nsec;
    }
    printf("Addition time [ns]: %ld\n", elapsed_time);

    // Check work.
    //
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        if (sum[i] != ARRAY_SIZE) {
            fprintf(stderr, "sum[%ld] has incorrect value of %d.\n", i, sum[i]);
	    return -1;
	}
    }

    free(a);
    free(b);
    free(sum);
    return 0;
}

// Set up the arrays in memory.
//
void setup_data(int *a, int *b) {
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        a[i] = i;
	b[i] = ARRAY_SIZE - i;
    }
}

// Do the actual work.
//
void do_addition(int *a, int *b, int *sum) {
    for (size_t i = 0; i < ARRAY_SIZE; i++) {
        sum[i] = a[i] + b[i];
    }
}
