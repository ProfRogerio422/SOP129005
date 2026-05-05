#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_CONEXOES 3
#define TOTAL_THREADS 10

sem_t banco_de_dados;

void* realizar_conexao(void* arg) {
    long id = (long)arg;

    printf("[Thread %ld] Tentando conectar ao banco...\n", id);

    // Tenta adquirir uma das 3 "vagas"
    sem_wait(&banco_de_dados);

    // --- Início da Seção Crítica (Acesso ao Recurso) ---
    printf("  >>> [Thread %ld] CONECTADA. (Usando 1 de %d vagas)\n", id, MAX_CONEXOES);
    
    // Simula processamento no banco de dados
    sleep(2); 

    printf("  <<< [Thread %ld] Desconectando e liberando vaga...\n", id);
    // --- Fim da Seção Crítica ---

    sem_post(&banco_de_dados);

    return NULL;
}

int main() {
    pthread_t threads[TOTAL_THREADS];

    // Inicializa o semáforo com 3 (Permite 3 acessos simultâneos)
    sem_init(&banco_de_dados, 0, MAX_CONEXOES);

    printf("Iniciando simulação. Limite de conexões: %d\n\n", MAX_CONEXOES);

    for (long i = 0; i < TOTAL_THREADS; i++) {
        pthread_create(&threads[i], NULL, realizar_conexao, (void*)i);
    }

    for (int i = 0; i < TOTAL_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&banco_de_dados);
    printf("\nSimulação finalizada.\n");

    return 0;
}