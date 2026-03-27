#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int saldo = 100; // Variável compartilhada (Recurso Crítico)

// Thread 1: Incrementa o valor lentamente
void* thread_incrementa(void* arg) {
    for (int i = 0; i < 20; i++) {
        saldo++;
        printf("[Thread +] Incrementou! Saldo atual: %d\n", saldo);
        usleep(600000); // Dorme por 600ms (mais lenta)
    }
    return NULL;
}

// Thread 2: Decrementa o valor rapidamente
void* thread_decrementa(void* arg) {
    for (int i = 0; i < 20; i++) {
        saldo--;
        printf("[Thread -] Decrementou! Saldo atual: %d\n", saldo);
        usleep(100000); // Dorme por 100ms (mais rápida)
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    printf("Saldo Inicial: %d\n", saldo);
    printf("Iniciando a competição entre threads...\n\n");

    pthread_create(&t1, NULL, thread_incrementa, NULL);
    pthread_create(&t2, NULL, thread_decrementa, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("\nResultado Final: %d\n", saldo);
    printf("Nota: O valor tende a baixar mais rápido devido ao intervalo de sono menor da Thread 2.\n");

    return 0;
}