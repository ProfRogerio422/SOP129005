#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Thread 1: CPU Bound - Muito Lenta (Simula Processamento de Vídeo)
void* tarefa_lenta_cpu(void* arg) {
    printf("[Thread 1] Iniciando Processamento Pesado (CPU Bound)...\n");
    sleep(8); 
    printf("[Thread 1] COMPLETA após 8 segundos.\n");
    pthread_exit(NULL);
}

// Thread 2: I/O Bound - Média (Simula Busca em Banco de Dados)
void* tarefa_media_io(void* arg) {
    printf("[Thread 2] Consultando Banco de Dados (I/O Bound)...\n");
    sleep(5);
    printf("[Thread 2] COMPLETA após 5 segundos.\n");
    pthread_exit(NULL);
}

// Thread 3: Cache - Muito Rápida (Simula Verificação de Sessão)
void* tarefa_rapida_cache(void* arg) {
    printf("[Thread 3] Verificando Cache (A mais rápida!)...\n");
    sleep(1);
    printf("[Thread 3] COMPLETA após 1 segundo.\n");
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2, t3;

    printf("=== INICIANDO BACK-END (PID: %d) ===\n", getpid());

    // Criando na ordem: Lenta -> Média -> Rápida
    printf("Criando Thread 1 (Lenta)...\n");
    pthread_create(&t1, NULL, tarefa_lenta_cpu, NULL);

    printf("Criando Thread 2 (Média)...\n");
    pthread_create(&t2, NULL, tarefa_media_io, NULL);

    printf("Criando Thread 3 (Rápida - Chamada por último)...\n");
    pthread_create(&t3, NULL, tarefa_rapida_cache, NULL);

    printf("\n--- Todas as threads foram disparadas. Aguardando... ---\n\n");

    // O Join espera todas, mas a ordem de saída no console mostrará a Thread 3 terminando antes
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\n=== SISTEMA FINALIZADO ===\n");
    return 0;
}