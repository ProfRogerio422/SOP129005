#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h> // Incluída para usar semáforos

#define NUM_THREADS 100
#define NUM_STEPS 100000

int sum = 0;
sem_t s; // Declaração do semáforo

void *threadBody(void *id) {
    int i;

    for (i = 0; i < NUM_STEPS; i++) {
        // --- Entrada na Seção Crítica ---
        // P(s) ou sem_wait: decrementa o semáforo. 
        // Se for 0, a thread dorme até que alguém dê um post.
        sem_wait(&s);
        
        // --- Seção Crítica ---
        sum += 1; 
        
        if (sum % 100000 == 0) 
            printf("Sum: %d\n", sum);
        
        // --- Saída da Seção Crítica ---
        // V(s) ou sem_post: incrementa o semáforo, liberando o próximo.
        sem_post(&s);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    long expected = (long)NUM_THREADS * NUM_STEPS;

    // Inicializa o semáforo:
    // 2º param (0): compartilhado entre threads.
    // 3º param (1): valor inicial (permite 1 acesso por vez).
    sem_init(&s, 0, 1);

    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, threadBody, (void *)i) != 0) {
            perror("Falha ao criar thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n--- Resultado: Semáforo POSIX ---\n");
    printf("Valor esperado: %ld\n", expected);
    printf("Valor obtido:   %d\n", sum);
    printf("Diferença:      %ld\n", expected - sum);

    // Destrói o semáforo ao final
    sem_destroy(&s);

    return 0;
}