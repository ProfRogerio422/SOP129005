#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct { float temp; int pres; } Dados;

int main() {
    // Cria a memória
    int fd = shm_open("/sensor_data", O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(Dados));
    
    // Mapeia para um ponteiro do tipo da nossa Struct
    Dados *ptr = mmap(NULL, sizeof(Dados), PROT_WRITE, MAP_SHARED, fd, 0);

    while(1) {
        ptr->temp = 25.0 + (rand() % 10); // Simula variação de temperatura
        ptr->pres = 100 + (rand() % 20);  // Simula variação de pressão
        
        printf("[SENSOR] Dados atualizados na RAM: %.1f°C, %d atm\n", ptr->temp, ptr->pres);
        sleep(1);
    }
    return 0;
}
