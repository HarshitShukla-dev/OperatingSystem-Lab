#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

int main()
{
    int fd;
    char *fifo = "/home/admin/Practice/Exp8/myfifo.txt"; // name of the named pipe
    char buffer[BUFFER_SIZE];

    // create the named pipe
    mkfifo(fifo, 0666);

    // open the named pipe for reading
    fd = open(fifo, O_RDONLY);

    // read from the named pipe
    read(fd, buffer, BUFFER_SIZE);

    // print the message received from the named pipe
    printf("Received message: %s\n", buffer);

    // close the named pipe
    close(fd);

    // remove the named pipe
    unlink(fifo);

    return 0;
}
