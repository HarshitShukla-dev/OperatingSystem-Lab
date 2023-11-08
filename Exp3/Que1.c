#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

int main() {
    int src_fd = open("input.txt", O_RDONLY);

    int dest_fd = open("output1.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);

    off_t file_size = lseek(src_fd, 0, SEEK_END);

    off_t copy_size = file_size / 2;

    lseek(src_fd, 0, SEEK_SET);

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    off_t total_bytes_copied = 0;

    while (total_bytes_copied < copy_size) {
        bytes_read = read(src_fd, buffer, 8);

        bytes_written = write(dest_fd, buffer, bytes_read);

        total_bytes_copied += bytes_written;
    }

    close(src_fd);
    close(dest_fd);

    printf("Copied %ld bytes from input.txt to output1.txt\n", total_bytes_copied);

    return 0;
}
