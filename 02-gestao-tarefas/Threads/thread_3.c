#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
void* tarefa(void* arg) {
    int id = *(int*)arg;
    while(1) { // Mantém a thread viva para observação
        printf("Thread %d ativa...\n", id);
        sleep(2);
    }
    return NULL;
}
int main() {
    pthread_t t[5];
    int ids[5];
    for(int i=0; i<5; i++) {
        ids[i] = i+1;
        pthread_create(&t[i], NULL, tarefa, &ids[i]);
    }
    for(int i=0; i<5; i++) pthread_join(t[i], NULL);
    return 0;
}