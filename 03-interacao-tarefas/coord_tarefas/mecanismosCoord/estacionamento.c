#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define TOTAL_VAGAS 5
#define TOTAL_CARROS 10

sem_t vagas;

void* entrar_no_estacionamento(void* arg) {
    int id = *(int*)arg;
    free(arg);

    printf("Carro %d chegou e está procurando vaga...\n", id);

    // Se não houver vaga, o semáforo bloqueia aqui
    sem_wait(&vagas);

    printf("--> Carro %d ENTROU.\n", id);

    // Tempo de permanência maior para visualizar o bloqueio
    sleep(5 + rand() % 6);

    printf("<-- Carro %d SAIU. Liberando vaga...\n", id);

    // Libera a vaga
    sem_post(&vagas);

    return NULL;
}

int main() {
    pthread_t carros[TOTAL_CARROS];
    srand(time(NULL));

    // Inicializa semáforo com número de vagas
    sem_init(&vagas, 0, TOTAL_VAGAS);

    for (int i = 0; i < TOTAL_CARROS; i++) {
        int* id = malloc(sizeof(int));
        *id = i + 1;

        pthread_create(&carros[i], NULL, entrar_no_estacionamento, id);
        usleep(200000); // chegada gradual
    }

    for (int i = 0; i < TOTAL_CARROS; i++) {
        pthread_join(carros[i], NULL);
    }

    sem_destroy(&vagas);
    printf("\nEstacionamento encerrado.\n");
    return 0;
}
