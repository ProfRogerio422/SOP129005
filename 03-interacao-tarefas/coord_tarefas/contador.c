#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 100
#define NUM_STEPS 100000

int sum = 0;

void *threadBody(void *id) {
    int i;
    for (i = 0; i < NUM_STEPS; i++) {       
        sum += 1; 
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    long expected = (long)NUM_THREADS * NUM_STEPS;

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, threadBody, NULL) != 0) {
            perror("Falha ao criar thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("--- Demonstração de Condição de Corrida ---\n");
    printf("Valor esperado (N * steps): %ld\n", expected);
    printf("Valor obtido no contador:   %d\n", sum);
    printf("Diferença (Perda de dados): %ld\n", expected - sum);

    return 0;
}