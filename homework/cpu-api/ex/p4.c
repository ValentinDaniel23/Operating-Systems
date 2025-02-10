#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork(); // Fork to create a new process

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0)
    { // Child process
        // execl() - passing each argument explicitly
        printf("Using execl():\n");
        execl("/bin/ls", "ls", "-l", (char *)NULL);

        // execle() - passing the environment pointer
        printf("Using execle():\n");
        char *env[] = {"PATH=/bin", NULL};
        execle("/bin/ls", "ls", "-l", (char *)NULL, env);

        // execlp() - searching for ls in the PATH
        printf("Using execlp():\n");
        execlp("ls", "ls", "-l", (char *)NULL);

        // execv() - passing arguments as an array
        printf("Using execv():\n");
        char *args[] = {"ls", "-l", NULL};
        execv("/bin/ls", args);

        // execvp() - searching for ls in the PATH and passing arguments as an array
        printf("Using execvp():\n");
        execvp("ls", args);

        // execvpe() - searching for ls in the PATH and passing arguments as an array with environment
        printf("Using execvpe():\n");
        execvpe("ls", args, env);

        // If exec fails
        perror("Exec failed");
        exit(1);
    }
    else
    { // Parent process
        // Wait for the child process to complete (optional)
        wait(NULL);
        printf("Parent process complete.\n");
    }

    return 0;
}
