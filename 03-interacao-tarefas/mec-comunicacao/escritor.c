#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    // 1. Cria o objeto de memória "/meu_quadro"
    int fd = shm_open("/meu_quadro", O_CREAT | O_RDWR, 0666);
    
    // 2. Define o tamanho para 4 bytes (tamanho de um int)
    ftruncate(fd, sizeof(int));
    
    // 3. Mapeia e recebe o ponteiro 'ptr'
    int *ptr = mmap(NULL, sizeof(int), PROT_WRITE, MAP_SHARED, fd, 0);
    
    // 4. Escreve o número 42 na memória
    printf("Escritor: Colocando o segredo 42 na memória...\n");
    *ptr = 42; 
    
    munmap(ptr, sizeof(int));
    close(fd);
    return 0;
}
