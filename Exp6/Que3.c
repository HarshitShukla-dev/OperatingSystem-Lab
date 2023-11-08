#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

int arr[100];
int n;

void *average(void *arg) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }
    printf("Average: %d\n", sum / n);
}

void *maximum(void *arg) {
    int max = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    printf("Maximum: %d\n", max);
}

void *minimum(void *arg) {
    int min = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    printf("Minimum: %d\n", min);
}

int main(){
    pthread_t tid1, tid2, tid3;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    pthread_create(&tid1, NULL, average, NULL);
    pthread_create(&tid2, NULL, maximum, NULL);
    pthread_create(&tid3, NULL, minimum, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    return 0;
}

