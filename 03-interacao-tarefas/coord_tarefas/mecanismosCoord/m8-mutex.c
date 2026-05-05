#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 100
#define NUM_STEPS 100000

int sum = 0;
// Substituímos sem_t por pthread_mutex_t
pthread_mutex_t lock; 

void *threadBody(void *id) {
    long my_id = (long)id;
    int i;

    for (i = 0; i < NUM_STEPS; i++) {
        // --- Entrada na Seção Crítica ---
        // pthread_mutex_lock equivale ao sem_wait()
        pthread_mutex_lock(&lock);
        
        // --- Seção Crítica ---
        sum += 1; 
        
        if (sum % 100000 == 0) 
            printf("Thread %ld incrementou. Sum: %d\n", my_id, sum);
        
        // --- Saída da Seção Crítica ---
        // pthread_mutex_unlock equivale ao sem_post()
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    long expected = (long)NUM_THREADS * NUM_STEPS;

    // Inicializa o mutex com atributos padrão (NULL)
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n Falha na inicialização do mutex\n");
        return 1;
    }

    for (long i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, threadBody, (void *)i) != 0) {
            perror("Falha ao criar thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n--- Resultado: Pthread Mutex ---\n");
    printf("Valor esperado: %ld\n", expected);
    printf("Valor obtido:   %d\n", sum);
    printf("Diferença:      %ld\n", expected - sum);

    // Destrói o mutex ao final
    pthread_mutex_destroy(&lock);

    return 0;
}