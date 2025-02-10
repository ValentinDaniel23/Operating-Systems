#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork(); // Create a new child process

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0)
    { // Child process
        // Close standard output (STDOUT_FILENO)
        close(STDOUT_FILENO);

        // Try to print something, but since STDOUT is closed, it will not show up
        printf("This should not be printed.\n");

        // Optionally, you can check the return value of write to verify
        if (write(STDOUT_FILENO, "Direct write to STDOUT after close.\n", 35) == -1)
        {
            perror("Write failed");
        }

        // Child exits
        exit(0);
    }
    else
    { // Parent process
        // Parent process can still print to STDOUT
        printf("This will be printed by the parent process.\n");

        // Wait for the child process to finish
        wait(NULL);
    }

    return 0;
}
