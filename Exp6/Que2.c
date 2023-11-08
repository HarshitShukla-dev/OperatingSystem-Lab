#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void *length(void *arg) {
    char *str = (char *)arg;
    int len = strlen(str);
    printf("%d\n", len);
}

int main(){
    pthread_t tid;
    char *str = "Harshit";
    pthread_create(&tid, NULL, length, (void *)str);
    pthread_join(tid, NULL);
    return 0;
}

