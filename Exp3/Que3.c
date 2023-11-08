#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, n;
    char ch;

    fd = open("input.txt", O_RDONLY);

    while ((n = read(fd, &ch, 1)) > 0) {
        write(STDOUT_FILENO, &ch, 1);
    }

    close(fd);

    return 0;
}
