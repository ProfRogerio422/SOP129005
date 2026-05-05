#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t trava_impressora = PTHREAD_MUTEX_INITIALIZER;

void* imprimir_relatorio(void* arg) {
    char* nome_pc = (char*)arg;

    // Tenta pegar a "chave" da impressora
    pthread_mutex_lock(&trava_impressora);

    // Seção Crítica: Onde o recurso é usado
    printf("Computador [%s] começou a imprimir...\n", nome_pc);
    for(int i = 1; i <= 3; i++) {
        printf("Computador [%s]: Imprimindo página %d...\n", nome_pc, i);
        sleep(1); // Simula o tempo da impressão
    }
    printf("Computador [%s] terminou e liberou a impressora!\n\n", nome_pc);

    // Libera a "chave" para o próximo
    pthread_mutex_unlock(&trava_impressora);

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