#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MSG_SIZE 100

// Define the message structure
struct message {
    long mtype;
    char mtext[MSG_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate a unique key
    key = ftok("que2.c", 'b');

    // Create a message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Send a message
    msg.mtype = 1;
    strcpy(msg.mtext, "Hello, this is a message!");
    msgsnd(msgid, &msg, sizeof(msg), 0);

    // Receive a message
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);
    printf("Received message: %s\n", msg.mtext);

    // Destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
