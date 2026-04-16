#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    // 1. Abre a memória
    int fd = shm_open("/meu_quadro", O_RDONLY, 0666);
    if (fd == -1) {
        perror("Erro: O escritor ja rodou? shm_open");
        exit(1);
    }
    
    // 2. Mapeia
    int *ptr = mmap(NULL, sizeof(int), PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }
    
    // 3. Agora sim é seguro ler
    printf("Leitor: Eu vi no quadro o valor: %d\n", *ptr);
    
    // 4. Limpeza
    munmap(ptr, sizeof(int));
    close(fd);
    shm_unlink("/meu_quadro"); 
    
    return 0;
}
