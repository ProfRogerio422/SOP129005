#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Função da Thread 1: Manipulação de Arquivo (I/O)
void* tarefa_arquivo(void* arg) {
    FILE *fp;
    for (int i = 1; i <= 10; i++) {
        fp = fopen("log_threads.txt", "a");
        if (fp == NULL) {
            perror("Erro ao abrir arquivo");
            pthread_exit(NULL);
        }
        fprintf(fp, "Log da Thread Escritora - Passo %d\n", i);
        fclose(fp);
        
        printf("[Thread Escrita] Escreveu no arquivo e aguardando...\n");
        sleep(1); // Simula latência de disco
    }
    printf("--- Thread Escrita Finalizada ---\n");
    return NULL;
}

// Função da Thread 2: Processamento Paralelo
void* tarefa_calculo(void* arg) {
    for (int i = 1; i <= 5; i++) {
        printf("[Thread Calculo] Processando lógica matemática... (Passo %d)\n", i);
        sleep(2); // Simula uma tarefa de processamento diferente
    }
    printf("--- Thread Calculo Finalizada ---\n");
    return NULL;
}

int main() {
    pthread_t t1, t2;

    printf("Iniciando processo (PID: %d)...\n", getpid());

    // Cria as duas threads com funções distintas
    pthread_create(&t1, NULL, tarefa_arquivo, NULL);
    pthread_create(&t2, NULL, tarefa_calculo, NULL);

    // Aguarda ambas terminarem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Processo principal encerrado.\n");
    return 0;
}