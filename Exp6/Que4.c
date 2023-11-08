#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10

int originalArray[ARRAY_SIZE];
int sortedArray[ARRAY_SIZE];

void bubbleSort(int arr[], int start, int end) {
    for (int i = start; i <= end; i++) {
        for (int j = start; j <= end - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void merge(int left[], int right[], int merged[], int leftSize, int rightSize) {
    int i = 0, j = 0, k = 0;

    while (i < leftSize && j < rightSize) {
        if (left[i] < right[j])
            merged[k++] = left[i++];
        else
            merged[k++] = right[j++];
    }

    while (i < leftSize)
        merged[k++] = left[i++];

    while (j < rightSize)
        merged[k++] = right[j++];
}

void* sort(void* arg) {
    int* params = (int*)arg;
    int start = params[0];
    int end = params[1];

    bubbleSort(originalArray, start, end);

    return NULL;
}

int main() {
    pthread_t threads[3];
    int threadParams[3][2] = {
        {0, ARRAY_SIZE / 2 - 1},
        {ARRAY_SIZE / 2, ARRAY_SIZE - 1},
        {0, ARRAY_SIZE - 1}
    };

    printf("Enter %d integers for the original array:\n", ARRAY_SIZE);
    for (int i = 0; i < ARRAY_SIZE; i++) {
        scanf("%d", &originalArray[i]);
    }

    printf("Original Array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", originalArray[i]);
    }
    printf("\n");

    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, sort, threadParams[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_create(&threads[2], NULL, sort, threadParams[2]);
    pthread_join(threads[2], NULL);

    int leftSize = ARRAY_SIZE / 2;
    int rightSize = ARRAY_SIZE - leftSize;

    int left[leftSize];
    int right[rightSize];

    for (int i = 0; i < leftSize; i++) {
        left[i] = originalArray[i];
    }

    for (int i = 0; i < rightSize; i++) {
        right[i] = originalArray[leftSize + i];
    }

    merge(left, right, sortedArray, leftSize, rightSize);



    printf("Sorted Array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", sortedArray[i]);
    }
    printf("\n");

    return 0;
}
