#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>

// Brute-force algorithm - O(n^3)
int max_subarray_sum_brute(int *a, int n) {
    int best = INT_MIN;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            int sum = 0;
            for (int k = i; k <= j; k++) {
                sum += a[k];
            }
            if (sum > best)
                best = sum;
        }
    }
    return best;
}

// Improved algorithm - O(n^2)
int max_subarray_sum_improved(int *a, int n) {
    int best = INT_MIN;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += a[j];
            if (sum > best)
                best = sum;
        }
    }
    return best;
}

// Kadane's algorithm - O(n)
int max_subarray_sum_kadane(int *a, int n) {
    int best = INT_MIN, sum = 0;
    for (int i = 0; i < n; i++) {
        sum = (sum + a[i] > a[i]) ? sum + a[i] : a[i];
        best = (sum > best) ? sum : best;
    }
    return best;
}

// Generates array with random values in range [-25, 74]
int* generate_input(int size) {
    srand(time(NULL));
    int *a = malloc(size * sizeof(int));
    if (!a) {
        perror("Memory allocation failed");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        a[i] = rand() % 100 - 25;
    }
    return a;
}

// Measures execution time in seconds
double measure(int (*f)(int*, int), int *input, int size, const char *label) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    int result = f(input, size);
    gettimeofday(&end, NULL);
    
    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_usec - start.tv_usec) / 1e6;

    printf("%s result: %d, time: %.6f seconds\n", label, result, elapsed);
    return elapsed;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return 1;
    }

    int size = atoi(argv[1]);
    int *input = generate_input(size);

    measure(max_subarray_sum_brute, input, size, "Brute force (O(n^3))");
    measure(max_subarray_sum_improved, input, size, "Improved (O(n^2))");
    measure(max_subarray_sum_kadane, input, size, "Kadane (O(n))");

    free(input);
    return 0;
}