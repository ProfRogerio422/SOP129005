#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    // 1. Abre a memória que já foi criada pelo outro programa
    int fd = shm_open("/meu_quadro", O_RDONLY, 0666);
    
    // 2. Mapeia para poder ler (PROT_READ)
    int *ptr = mmap(NULL, sizeof(int), PROT_READ, MAP_SHARED, fd, 0);
    
    // 3. Lê o valor que está lá
    printf("Leitor: Eu vi no quadro o valor: %d\n", *ptr);
    
    // 4. Limpeza: fecha e remove a memória do sistema
    munmap(ptr, sizeof(int));
    close(fd);
    shm_unlink("/meu_quadro"); 
    
    return 0;
}
