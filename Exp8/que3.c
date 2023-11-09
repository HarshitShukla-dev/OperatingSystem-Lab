#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SIZE 100

// Define message structure
struct message {
    long mtype;
    char mtext[MAX_SIZE];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;

    // Generate unique key
    key = ftok("que3.c", 'b');

    // Create message queue
    msgid = msgget(key, 0666 | IPC_CREAT);

    // Send message
    msg.mtype = 1;
    printf("Enter message: ");
    fgets(msg.mtext, MAX_SIZE, stdin);
    msgsnd(msgid, &msg, sizeof(msg), 0);
    printf("Message sent: %s", msg.mtext);

    // Receive message
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);
    printf("Message received: %s", msg.mtext);

    // Destroy message queue
    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
