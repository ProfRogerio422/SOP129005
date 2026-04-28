#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 100
#define NUM_STEPS 100000

int sum = 0;
int busy = 0; // Flag: 0 = livre, 1 = ocupado

void enter_cs() {
    // Protocolo de entrada: espera ocupada
    while (busy == 1); 
    
    // Marca como ocupado
    busy = 1;
}

void leave_cs() {
    // Protocolo de saída: libera a seção crítica
    busy = 0;
}

void *threadBody(void *id) {
    int i;
    for (i = 0; i < NUM_STEPS; i++) {
        enter_cs();
        
        // --- SEÇÃO CRITICA ---
        sum += 1; 
        
        leave_cs();
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

    printf("--- Resultado com Solução Trivial (Flag busy) ---\n");
    printf("Valor esperado: %ld\n", expected);
    printf("Valor obtido:   %d\n", sum);
    printf("Diferença:      %ld\n", expected - sum);

    return 0;
}