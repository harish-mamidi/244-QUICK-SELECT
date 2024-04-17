#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Partition function to rearrange the elements around a pivot
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Choose the last element as the pivot
    int i = low - 1; // Index of smaller element
     int j;
    for ( j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Recursive function to find the kth smallest element
int quickSelect(int arr[], int low, int high, int k) {
    if (low <= high) {
        int pivotIndex = partition(arr, low, high);

        // If pivot itself is the kth smallest element
        if (pivotIndex == k) return arr[pivotIndex];

        // If kth smallest element is in the left subarray
        if (pivotIndex > k) return quickSelect(arr, low, pivotIndex - 1, k);

        // If kth smallest element is in the right subarray
        return quickSelect(arr, pivotIndex + 1, high, k);
    }
    return -1; // Return -1 if k is out of range
}

int main() {
    FILE *file;
    char filename[100];
    int n,i, k;

    printf("Enter the name of the CSV file: ");
    scanf("%s", filename);

    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(file, "%d", &n);
    
    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for ( i = 0; i < n; ++i) {
        fscanf(file, "%d,", &arr[i]);
    }

    fclose(file);
    
    printf("Enter the value of k (1-based index): ");
    scanf("%d", &k);

    int result = quickSelect(arr, 0, n - 1, k - 1);
    if (result != -1)
        printf("The %dth smallest element is: %d\n", k, result);
    else
        printf("Invalid input!\n");

    free(arr);
    return 0;
}

