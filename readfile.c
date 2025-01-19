#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFF_SIZE 2048

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        write(2, "Specify file path: ./readfile <filename>\n", 29);
        return 1;
    }

    char *filename = argv[1];

    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Open File Error");
        return 1;
    }

    char buffer[BUFF_SIZE];

    ssize_t num_bytes = read(fd, buffer, BUFF_SIZE);
    if (num_bytes == -1)
    {
        perror("Read File Error");
        close(fd);
        return 1;
    }

    if (write(1, buffer, num_bytes) == -1)
    {
        perror("Write File Error");
        close(fd);
        return 1;
    }
    close(fd);
}