#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_READERS 10

int shared_variable = 0;
int readers_count = 0;
sem_t mutex, write_block;
pthread_t readers[MAX_READERS], writer;

void *reader(void *arg) {
    int reader_id = *(int*)arg;
    while (1) {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&write_block);
        }
        sem_post(&mutex);

        printf("Reader %d read shared variable: %d\n", reader_id, shared_variable);

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&write_block);
        }
        sem_post(&mutex);

        sleep(1);
    }
}

void *writer_func(void *arg) {
    while (1) {
        sem_wait(&write_block);

        shared_variable++;
        printf("Writer wrote shared variable: %d\n", shared_variable);

        sem_post(&write_block);

        sleep(1);
    }
}

int main() {
    sem_init(&mutex, 0, 1);
    sem_init(&write_block, 0, 1);

    int i, reader_id[MAX_READERS];
    for (i = 0; i < MAX_READERS; i++) {
        reader_id[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_id[i]);
    }

    pthread_create(&writer, NULL, writer_func, NULL);

    for (i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    pthread_join(writer, NULL);

    sem_destroy(&mutex);
    sem_destroy(&write_block);

    return 0;
}
