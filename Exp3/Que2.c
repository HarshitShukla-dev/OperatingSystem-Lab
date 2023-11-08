#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, n;
    char ch;

    fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    
    printf("Enter text (terminate with '$'): \n");

    while ((n = read(STDIN_FILENO, &ch, 1)) > 0) {
        write(fd, &ch, 1);

        if (ch == '$') {
            break;
        }
    }

    close(fd);

    printf("Input saved to output.txt\n");

    return 0;
}
