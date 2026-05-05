#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Recursos globais
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond  = PTHREAD_COND_INITIALIZER;

int pronto = 0; // Esta é a nossa condição real

void* worker(void* arg) {
    long id = (long)arg;

    printf("Thread %ld: Cheguei e estou esperando o sinal...\n", id);

    pthread_mutex_lock(&mutex);    
   
    while (pronto == 0) {
        // pthread_cond_wait faz 3 coisas:
        // 1. Libera o mutex automaticamente para outros usarem.
        // 2. Coloca a thread para dormir.
        // 3. Ao ser sinalizada, ela acorda e re-adquire o mutex.
        pthread_cond_wait(&cond, &mutex);
    }

    printf("Thread %ld: Recebi o sinal! Trabalhando...\n", id);
    
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, worker, (void*)1);
    pthread_create(&t2, NULL, worker, (void*)2);

    sleep(2); // Simula o tempo que o "chefe" leva para preparar algo

    printf("Main: Preparando tudo... agora vou dar o sinal!\n");

    pthread_mutex_lock(&mutex);
    pronto = 1; // Altera a condição
    // pthread_cond_broadcast acorda TODAS as threads esperando
    // pthread_cond_signal acordaria apenas uma.
    pthread_cond_broadcast(&cond); 
    pthread_mutex_unlock(&mutex);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main: Finalizado.\n");
    return 0;
}