#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void create_children(int n) {
    int i;
    for (i = 0; i <= n; i++) {
        if (fork() == 0) {
            printf("Child process %d (PID: %d)\n", i + 1, getpid());
        } else {
            wait(NULL);
            break;
        }
    }
}

int main() {
    int n;
    printf("Enter the number of fork calls (n): ");
    scanf("%d", &n);

    printf("Parent process (PID: %d)\n", getpid());
    create_children(n);

    return 0;
}
