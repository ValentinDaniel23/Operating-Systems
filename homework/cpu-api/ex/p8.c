#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int pipe_fd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create the first child process
    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0)
    {
        // Child 1: Write to pipe
        close(pipe_fd[0]); // Close the read end of the pipe
        char msg[] = "Hello from child 1!\n";
        write(pipe_fd[1], msg, strlen(msg)); // Write to the pipe
        close(pipe_fd[1]);                   // Close the write end after writing
        exit(0);
    }

    // Create the second child process
    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0)
    {
        // Child 2: Read from pipe
        close(pipe_fd[1]); // Close the write end of the pipe
        char buffer[256];
        read(pipe_fd[0], buffer, sizeof(buffer));       // Read from the pipe
        printf("Child 2 received message: %s", buffer); // Print the received message
        close(pipe_fd[0]);                              // Close the read end after reading
        exit(0);
    }

    // Parent process: Wait for both children to finish
    close(pipe_fd[0]); // Close both ends in the parent
    close(pipe_fd[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}
