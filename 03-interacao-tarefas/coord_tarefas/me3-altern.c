#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 100
#define NUM_STEPS 100000

int sum = 0;
int turn = 0; // Indica de qual thread é a vez

void enter_cs(long int id) {
    // Espera ocupada até que o valor de turn seja igual ao meu ID
    while (turn != id); 
    
    if (sum % 100 == 0)
    printf ("Turn: %d, Sum: %d\n", turn, sum) ;
    
}

void leave_cs() {
    // Passa o turno para a próxima thread (circular)
    turn = (turn + 1) % NUM_THREADS;
}

void *threadBody(void *id) {
    long my_id = (long)id;
    int i;

    for (i = 0; i < NUM_STEPS; i++) {
        enter_cs(my_id);
        
        // --- Seção Critica ---
        sum += 1; 
        
        leave_cs();
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    long expected = (long)NUM_THREADS * NUM_STEPS;

    for (long i = 0; i < NUM_THREADS; i++) {
        // Passamos o índice i como o ID da thread
        if (pthread_create(&threads[i], NULL, threadBody, (void *)i) != 0) {
            perror("Falha ao criar thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("--- Resultado: Alternância Estrita ---\n");
    printf("Valor esperado: %ld\n", expected);
    printf("Valor obtido:   %d\n", sum);
    printf("Diferença:      %ld\n", expected - sum);

    return 0;
}