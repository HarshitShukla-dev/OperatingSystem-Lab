#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *concatenate(void *arg) {
    char *str = (char *)arg;
    char *str1 = (char *)malloc(sizeof(char) * 100);
    strcpy(str1, str);
    strcat(str1, " ");
    strcat(str1, str);
    printf("%s\n", str1);
}

int main(){
    pthread_t tid;
    char *str = "Hello";
    pthread_create(&tid, NULL, concatenate, (void *)str);
    pthread_join(tid, NULL);
    return 0;
}