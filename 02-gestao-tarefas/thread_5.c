#include <pthread.h>
#include <stdio.h>
#include <unistd.h> // Para a função sleep()
#include <sys/types.h>

void* tarefa_demorada(void* arg) {
    int id = *(int*)arg;
    
    for (int i = 0; i < 30; i++) { // Roda por 30 segundos
        printf("Thread %d em execução (Passo %d)...\n", id, i);
        sleep(1);
    }
    printf("Thread %d finalizada!\n", id);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    printf("Processo Principal (PID: %d) iniciando...\n", getpid());
    printf("Dica: Abra outro terminal e digite 'top -H -p %d'\n", getpid());

    pthread_create(&t1, NULL, tarefa_demorada, &id1);
    pthread_create(&t2, NULL, tarefa_demorada, &id2);

    // Espera as threads terminarem
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Processo principal encerrado.\n");
    return 0;
}