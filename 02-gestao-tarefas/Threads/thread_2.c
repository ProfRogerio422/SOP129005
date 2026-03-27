#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* calcular_dobro(void* arg) {
    int valor = *(int*)arg; // Cast do ponteiro void para int
    printf("Thread: O dobro de %d é %d\n", valor, valor * 2);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    int numero = 10;

    pthread_create(&tid, NULL, calcular_dobro, (void*)&numero);
    pthread_join(tid, NULL);

    return 0;
}