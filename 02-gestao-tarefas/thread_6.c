#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 5

// Função que cada thread irá executar
void* tarefa_do_aluno(void* arg) {
    int id = *(int*)arg;
    
    // Liberamos a memória alocada para o ID
    free(arg);

    for (int i = 1; i <= 10; i++) {
        printf("[Thread %d] Executando passo %d/10...\n", id, i);
        
        // Faz a thread "dormir" por 2 segundos para podermos vê-la no terminal
        sleep(2); 
    }

    printf("--- Thread %d finalizou seu trabalho! ---\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    printf("Iniciando o programa com %d threads...\n", NUM_THREADS);
    printf("PID do processo: %d\n", getpid());

    for (int i = 0; i < NUM_THREADS; i++) {
        // Alocamos memória para o ID para evitar que o valor mude 
        // antes da thread conseguir ler (evita condição de corrida no argumento)
        int* id_envio = malloc(sizeof(int));
        *id_envio = i + 1;

        printf("Criando a thread %d...\n", *id_envio);
        
        if (pthread_create(&threads[i], NULL, tarefa_do_aluno, id_envio) != 0) {
            perror("Falha ao criar a thread");
            return 1;
        }
    }

    // O 'join' garante que a Main espere todas as 5 terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Todas as threads concluíram. O Restaurante (Processo) vai fechar.\n");
    return 0;
}