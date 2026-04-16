// shm.c - Exemplo de uso de memória compartilhada POSIX
// Compilação em Linux: cc -Wall shm.c -o shm -lrt

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(void) {
    int fd;          // descritor do arquivo da memória compartilhada
    int value;       // valor a ser escrito/lido
    int *ptr;        // ponteiro para a área mapeada

    // Passo 1: criar/abrir a área de memória compartilhada
    fd = shm_open("/sharedmem", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        perror("Erro ao abrir memória compartilhada (shm_open)");
        exit(1);
    }

    // Passo 2: ajustar o tamanho da área para comportar um inteiro
    if (ftruncate(fd, sizeof(value)) == -1) {
        perror("Erro ao ajustar tamanho da memória (ftruncate)");
        exit(1);
    }

    // Passo 3: mapear a área de memória para o espaço do processo
    ptr = mmap(NULL, sizeof(value), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("Erro ao mapear memória (mmap)");
        exit(1);
    }

    // Loop infinito: escreve e lê valores na memória compartilhada
   while (1) {
        value = random() % 1000;
        *ptr = value;
        printf("\n[ESCRITOR] Escrevi %d. Agora vou esperar 2 segundos...\n", value);
       // printf("--- Corra para o outro terminal e rode o intruso AGORA! ---\n");
        
        sleep(2); // Janela de tempo para o intruso agir -- aumento o valor para 5 segundos

        value = *ptr; 
        printf("[LEITOR] Li o valor: %d\n", value);
        
       // if (value == -999) {
      //      printf("!!! ALERTA: A memoria foi invadida por outro processo! !!!\n");
      //  } else {
//printf("Ok, ninguem mexeu na memoria.\n");
      //  }
    }

    return 0;
}
