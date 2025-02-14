#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define NUM_ITERATIONS 1000000

// Inline pentru a obține timpul CPU
static inline uint64_t rdtsc()
{
    uint64_t cycles;
    __asm__ volatile("rdtsc" : "=A"(cycles)); // Folosim instrucțiunea rdtsc
    return cycles;
}

int main()
{
    uint64_t start_time, end_time, total_time = 0;

    for (int i = 0; i < NUM_ITERATIONS; i++)
    {
        start_time = rdtsc(); // Începutul unui apel de system call
        // Apel null (0-byte read)
        read(0, NULL, 0);   // Apel system call real
        end_time = rdtsc(); // Sfârșitul apelului
        total_time += (end_time - start_time);
    }

    printf("Costul unui apel system call este: %lu cicluri CPU pe %d apeluri\n", total_time / NUM_ITERATIONS, NUM_ITERATIONS);
    return 0;
}
