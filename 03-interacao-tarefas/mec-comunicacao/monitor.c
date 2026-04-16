#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct { float temp; int pres; } Dados;

int main() {
    int fd = shm_open("/sensor_data", O_RDONLY, 0666);
    
    // Mapeia como leitura
    Dados *ptr = mmap(NULL, sizeof(Dados), PROT_READ, MAP_SHARED, fd, 0);

    while(1) {
        printf("[MONITOR] Lendo da RAM -> Temp: %.1f | Pressão: %d\n", ptr->temp, ptr->pres);
        sleep(2); // O monitor lê mais devagar que o sensor
    }
    return 0;
}
