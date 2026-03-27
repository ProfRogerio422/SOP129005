#include <pthread.h>
#include <stdio.h>

int contador = 0;

void* incrementar(void* arg) {
    for (int i = 0; i < 100000; i++) {
        contador++; // Região Crítica sem proteção
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, incrementar, NULL);
    pthread_create(&t2, NULL, incrementar, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // O resultado esperado seria 200.000, mas será menor devido à condição de corrida
    printf("Valor final do contador: %d\n", contador);
    return 0;
}