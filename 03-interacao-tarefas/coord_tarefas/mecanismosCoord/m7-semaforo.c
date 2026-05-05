#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 5
#define TOTAL_ITENS 15

int buffer[BUFFER_SIZE];
int index_prod = 0; // Onde o produtor coloca
int index_cons = 0; // De onde o consumidor tira

sem_t sem_vagas;   // Controla espaços vazios
sem_t sem_itens;   // Controla itens prontos
sem_t semaforo;       // Protege o acesso aos índices do buffer

void* produtor(void* arg) {
    for (int i = 0; i < TOTAL_ITENS; i++) {
        int item = rand() % 100; // Produz um número aleatório

        sem_wait(&sem_vagas); // Espera haver uma vaga (decrementa vagas)
        sem_wait(&semaforo);     // Entra na seção crítica

        // Coloca o item no buffer (circular)
        buffer[index_prod] = item;
        printf("[PRODUTOR] Produziu: %d na posição %d\n", item, index_prod);
        index_prod = (index_prod + 1) % BUFFER_SIZE;

        sem_post(&semaforo);     // Sai da seção crítica
        sem_post(&sem_itens); // Sinaliza que há um novo item (incrementa itens)

        usleep(rand() % 200000); // Simula tempo de produção
    }
    return NULL;
}

void* consumidor(void* arg) {
    for (int i = 0; i < TOTAL_ITENS; i++) {
        sem_wait(&sem_itens); // Espera haver um item (decrementa itens)
        sem_wait(&semaforo);     // Entra na seção crítica

        // Retira o item do buffer (circular)
        int item = buffer[index_cons];
        printf("  [CONSUMIDOR] Consumiu: %d da posição %d\n", item, index_cons);
        index_cons = (index_cons + 1) % BUFFER_SIZE;

        sem_post(&semaforo);     // Sai da seção crítica
        sem_post(&sem_vagas); // Sinaliza que há uma nova vaga (incrementa vagas)

        usleep(rand() % 500000); // Consumidor é mais lento que o produtor
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    srand(time(NULL));

    // Inicialização
    sem_init(&sem_vagas, 0, BUFFER_SIZE); // Começa com 5 vagas
    sem_init(&sem_itens, 0, 0);           // Começa com 0 itens
    sem_init(&semaforo, 0, 1);            // semaforo começa aberto (1)

    pthread_create(&t1, NULL, produtor, NULL);
    pthread_create(&t2, NULL, consumidor, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Limpeza
    sem_destroy(&sem_vagas);
    sem_destroy(&sem_itens);
    sem_destroy(&semaforo);

    printf("\nProcessamento concluído com sucesso.\n");
    return 0;
}