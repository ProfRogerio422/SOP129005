#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* tarefa(void* arg) {
    printf("Olá! Eu sou uma thread criada pelo processo principal. Estou Executando uma Tarefa\n");
    return NULL;
}

int main() {
    pthread_t tid; // Identificador da thread

    printf("Iniciando a thread...\n");
    pthread_create(&tid, NULL, tarefa, NULL);

    // Espera a thread terminar antes de encerrar o programa
    pthread_join(tid, NULL);
    
    printf("Thread finalizada. Encerrando o programa.\n");
    return 0;
}