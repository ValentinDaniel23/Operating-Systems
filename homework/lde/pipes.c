#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define NUM_ITERATIONS 1000

int main()
{
    int pipe1[2], pipe2[2];
    pid_t pid;
    clock_t start, end;

    // Crearea celor două pipe-uri
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1)
    {
        perror("Pipe creation failed");
        exit(1);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("Fork failed");
        exit(1);
    }

    start = clock();

    if (pid > 0)
    {
        // Procesul părinte
        char buf[10];
        for (int i = 0; i < NUM_ITERATIONS; i++)
        {
            // Scriem în primul pipe
            write(pipe1[1], "data", 4);
            // Așteptăm să citim din al doilea pipe
            read(pipe2[0], buf, 4);
        }
        wait(NULL); // Așteptăm procesul copil să termine
    }
    else
    {
        // Procesul copil
        char buf[10];
        for (int i = 0; i < NUM_ITERATIONS; i++)
        {
            // Citim din primul pipe
            read(pipe1[0], buf, 4);
            // Scriem în al doilea pipe
            write(pipe2[1], "data", 4);
        }
    }

    end = clock();
    double time_taken = ((double)end - start) / CLOCKS_PER_SEC;
    printf("Timp total pentru %d iterații de context switch: %f secunde\n", NUM_ITERATIONS, time_taken);

    return 0;
}
