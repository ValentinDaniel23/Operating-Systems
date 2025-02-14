#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#define NUM_ITERATIONS 1000000 // Poți ajusta acest număr pentru a avea un timp mai măsurabil

long long get_time_diff(struct timeval start, struct timeval end)
{
    long long diff = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    return diff;
}

int main()
{
    struct timeval start, end;
    long long total_time = 0;

    // Măsurăm timpul pentru NUM_ITERATIONS apeluri de system call
    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        gettimeofday(&start, NULL);
        // Apel null (0-byte read) pentru a simula un system call
        read(0, NULL, 0); // Apel system call real
        gettimeofday(&end, NULL);
        total_time += get_time_diff(start, end);
    }

    printf("%lld - %d\n", total_time, NUM_ITERATIONS);
    printf("Costul unui apel system call este: %f microsecunde pe %d apeluri\n", (double)total_time / NUM_ITERATIONS, NUM_ITERATIONS);
    return 0;
}
