#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond   = PTHREAD_COND_INITIALIZER;

int buffer_dados = 0; // Condição: 0 = vazio, >0 = tem dado

void* consume_data(void* arg) {
    pthread_mutex_lock(&mutex);
    
    while (buffer_dados == 0) { // Aguarda a presença de dados
        printf("Consumidor: Buffer vazio. Dormindo...\n");
        pthread_cond_wait(&cond, &mutex);
    }

    printf("Consumidor: Dado %d retirado do buffer!\n", buffer_dados);
    buffer_dados = 0; // Consumiu o dado
    
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void* produce_data(void* arg) {
    sleep(2); // Simula obtenção de dados de fonte externa
    
    pthread_mutex_lock(&mutex);
    
    buffer_dados = 42; // Deposita o dado
    printf("Produtor: Dados depositados no buffer.\n");
    
    pthread_cond_signal(&cond); // Sinaliza que o buffer contém dados
    
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main() {
    pthread_t c, p;
    pthread_create(&c, NULL, consume_data, NULL);
    pthread_create(&p, NULL, produce_data, NULL);
    pthread_join(c, NULL); pthread_join(p, NULL);
    return 0;
}