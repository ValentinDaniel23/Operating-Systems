#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

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
        printf("Child process: PID = %d\n", getpid());
        // Simulating some work in the child process
        sleep(2);
        printf("Child process is exiting\n");
        exit(42); // Exit with status code 42
    }
    else
    { // Parent process
        int status;
        printf("Parent process: Waiting for child to finish...\n");

        // Parent calls wait() to wait for the child process to finish
        pid_t child_pid = wait(&status); // Parent waits for the child to terminate

        if (child_pid < 0)
        {
            perror("Wait failed");
            return 1;
        }

        printf("%d\n", errno);
        // Checking how the child process terminated
        if (WIFEXITED(status))
        {
            printf("Child process (PID = %d) exited with status %d\n", child_pid, WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("Child process (PID = %d) terminated by signal %d\n", child_pid, WTERMSIG(status));
        }
        else
        {
            printf("Child process (PID = %d) terminated abnormally\n", child_pid);
        }
        printf("Parent process: Child finished\n");
    }

    return 0;
}
