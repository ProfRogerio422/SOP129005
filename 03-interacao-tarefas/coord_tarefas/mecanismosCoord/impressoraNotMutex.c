#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Removido o Mutex para demonstrar a falha

void* imprimir_relatorio(void* arg) {
    char* nome_pc = (char*)arg;

    // SEM MUTEX: As threads entram aqui simultaneamente
    printf("Computador [%s] começou a imprimir...\n", nome_pc);
    
    for(int i = 1; i <= 3; i++) {
        // Como não há trava, as linhas de A e B vão se intercalar
        printf("Computador [%s]: Imprimindo página %d...\n", nome_pc, i);
        usleep(100); // Pequeno atraso para forçar a troca de contexto
    }
    
    printf("Computador [%s] terminou!\n", nome_pc);

    return NULL;
}

int main() {
    pthread_t pc1, pc2;

    pthread_create(&pc1, NULL, imprimir_relatorio, "A");
    pthread_create(&pc2, NULL, imprimir_relatorio, "B");

    pthread_join(pc1, NULL);
    pthread_join(pc2, NULL);

    return 0;
}