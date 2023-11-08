#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    DIR *dp;
    struct dirent *dptr;
    int dir_created = mkdir("Dir1", 0777);
    
    if (dir_created == -1) {
        perror("mkdir");
        return 1;
    }

    char dir_path[] = "Dir1";
    char file_name[] = "my_file.txt";
    char filepath[100];

    strcpy(filepath, dir_path);
    strcat(filepath, "/");
    strcat(filepath, file_name);

    int file_fd = open(filepath, O_CREAT | O_WRONLY, 0666);

    if (file_fd == -1) {
        perror("open");
        return 1;
    }

    close(file_fd);

    dp = opendir(dir_path);
    
    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    while (NULL != (dptr = readdir(dp))) {
        printf("%s\n", dptr->d_name);
    }

    closedir(dp);

    return 0;
}
