#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("p1 (PID: %d, PPID: %d)\n", getpid(), getppid());

    pid_t p2_pid = fork();

    if (p2_pid == -1) {
        perror("Failed to create p2");
        return 1;
    }

    if (p2_pid == 0) {
        printf("p2 (PID: %d, PPID: %d)\n", getpid(), getppid());

        pid_t p3_pid = fork();

        if (p3_pid == -1) {
            perror("Failed to create p3");
            return 1;
        }

        if (p3_pid == 0) {
            printf("p3 (PID: %d, PPID: %d)\n", getpid(), getppid());
        } else {
            wait(NULL);
        }
    } else {
        wait(NULL);
    }

    return 0;
}
