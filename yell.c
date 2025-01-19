#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>

#define BUFF_SIZE 2048

void echo_input(int fd)
{
    char buffer[BUFF_SIZE];
    ssize_t num_bytes;

    while ((num_bytes = read(fd, buffer, BUFF_SIZE)) > 0)
    {
        for (ssize_t i = 0; i < num_bytes; i++)
        {
            buffer[i] = toupper(buffer[i]);
        }
        if (write(1, buffer, num_bytes) == -1)
        {
            perror("Write File Error");
            break;
        }
    }

    if (num_bytes == -1)
    {
        perror("Read File Error");
    }
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        echo_input(0);
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            int fd = open(argv[i], O_RDONLY);
            if (fd == -1)
            {
                perror(argv[i]);
                continue;
            }
            echo_input(fd);
            close(fd);
        }
    }
}