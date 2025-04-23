#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Comparison function for qsort
 * @param a Pointer to first element
 * @param b Pointer to second element
 * @return Negative if a < b, positive if a > b, zero if equal
 */
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Calculates the arithmetic mean of an integer array
 * @param arr Input array of integers
 * @param n Size of the array
 * @return Mean value as a float
 */
float calculate_mean(int arr[], int n) {
    if (n <= 0) return 0.0f;  // Handle empty array case
    
    long long sum = 0;  // Using long long to prevent integer overflow
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return (float)sum / n;
}

/**
 * Calculates the median of an integer array
 * @param arr Input array of integers
 * @param n Size of the array
 * @return Median value as a float
 */
float calculate_median(int arr[], int n) {
    if (n <= 0) return 0.0f;  // Handle empty array case
    
    // Create a copy of the array to avoid modifying the original
    int *sorted_arr = (int *)malloc(n * sizeof(int));
    if (sorted_arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 0.0f;
    }
    
    memcpy(sorted_arr, arr, n * sizeof(int));
    qsort(sorted_arr, n, sizeof(int), compare);
    
    float median;
    if (n % 2 == 0) {
        median = (sorted_arr[n/2 - 1] + sorted_arr[n/2]) / 2.0f;
    } else {
        median = sorted_arr[n/2];
    }
    
    free(sorted_arr);
    return median;
}

/**
 * Calculates and prints the mode of an integer array
 * @param arr Input array of integers
 * @param n Size of the array
 */
void calculate_mode(int arr[], int n) {
    if (n <= 0) {
        printf("Mode: No data available\n");
        return;
    }
    
    int max_count = 0;
    int mode = arr[0];  // Initialize with first element
    int current_count = 1;
    
    // Sort array first to make counting easier
    int *sorted_arr = (int *)malloc(n * sizeof(int));
    if (sorted_arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    
    memcpy(sorted_arr, arr, n * sizeof(int));
    qsort(sorted_arr, n, sizeof(int), compare);
    
    // Count occurrences of each number
    for(int i = 1; i < n; i++) {
        if(sorted_arr[i] == sorted_arr[i-1]) {
            current_count++;
        } else {
            if(current_count > max_count) {
                max_count = current_count;
                mode = sorted_arr[i-1];
            }
            current_count = 1;
        }
    }
    
    // Check last group
    if(current_count > max_count) {
        max_count = current_count;
        mode = sorted_arr[n-1];
    }
    
    printf("Mode: %d (appeared %d times)\n", mode, max_count);
    free(sorted_arr);
}

int main() {
    // Sample data array
    int data[] = {1, 2, 2, 3, 4};
    int n = sizeof(data)/sizeof(data[0]);
    
    // Calculate and display statistical measures
    printf("Dataset: [");
    for(int i = 0; i < n; i++) {
        printf("%d", data[i]);
        if(i < n-1) printf(", ");
    }
    printf("]\n");
    
    printf("Mean: %.2f\n", calculate_mean(data, n));
    printf("Median: %.2f\n", calculate_median(data, n));
    
    // Modified mode calculation to match Python output
    int max_count = 0;
    int modes[100];  // Assuming max 100 unique values
    int mode_count = 0;
    
    // Count frequencies
    int freq[100] = {0};  // Assuming values are between 0-99
    for(int i = 0; i < n; i++) {
        freq[data[i]]++;
        if(freq[data[i]] > max_count) {
            max_count = freq[data[i]];
            mode_count = 0;
            modes[mode_count++] = data[i];
        } else if(freq[data[i]] == max_count) {
            modes[mode_count++] = data[i];
        }
    }
    
    printf("Mode: [");
    for(int i = 0; i < mode_count; i++) {
        printf("%d", modes[i]);
        if(i < mode_count-1) printf("; ");
    }
    printf("]\n");
    
    return 0;
}
