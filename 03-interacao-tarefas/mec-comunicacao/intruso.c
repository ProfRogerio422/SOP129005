#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
    int fd = shm_open("/sharedmem", O_RDWR, 0666);
    int *ptr = mmap(NULL, sizeof(int), PROT_WRITE, MAP_SHARED, fd, 0);

    printf("Injetando valor intruso...\n");
    *ptr = -999; // Altera o valor diretamente na RAM compartilhada

    munmap(ptr, sizeof(int));
    close(fd);
    return 0;
}
