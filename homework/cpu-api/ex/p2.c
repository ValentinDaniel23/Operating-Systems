#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    // Open the file with the open() system call
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1)
    {
        perror("Failed to open file");
        return 1;
    }

    // Fork to create a child process
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0)
    { // Child process
        // Write to the file
        const char *child_message = "Child is writing to the file.\n";
        write(fd, child_message, strlen(child_message));
        close(fd); // Close the file descriptor
        return 0;
    }
    else
    { // Parent process
        // Write to the file
        const char *parent_message = "Parent is writing to the file.\n";
        write(fd, parent_message, strlen(parent_message));
        close(fd); // Close the file descriptor
        return 0;
    }
}
