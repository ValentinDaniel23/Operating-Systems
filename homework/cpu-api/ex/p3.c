#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork(); // Create a child process

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0)
    { // Child process
        // Child process prints "hello"
        printf("hello\n");
    }
    else
    { // Parent process
        // Sleep for a short time to allow child to execute first
        sleep(1); // Parent sleeps for 1 second

        // Parent process prints "goodbye"
        printf("goodbye\n");
    }

    return 0;
}
