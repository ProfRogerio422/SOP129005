// Arquivo mqsend.c: envia mensagens para uma fila de mensagens POSIX.
// Em Linux, compile usando: cc -Wall mqsend.c -o mqsend -lrt

#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <unistd.h>
#include <fcntl.h>   // necessário para O_RDWR

#define QUEUE "/my_queue"

int main (int argc, char *argv[])
{
    mqd_t queue;   // descritor da fila
    int msg;       // mensagem a enviar

    // abre a fila de mensagens, se existir
    if ((queue = mq_open(QUEUE, O_RDWR)) < 0)
    {
        perror("mq_open");
        exit(1);
    }

    for (;;)
    {
        // Geração de Dados Aleatórios
        msg = random() % 100; // valor entre 0 e 99

        // envia a mensagem
        if (mq_send(queue, (void*) &msg, sizeof(msg), 0) < 0)
        {
            perror("mq_send");
            exit(1);
        }
        printf("Sent message with value %d\n", msg);
        // esperar 1 segundo antes de enviar o próximo número
        sleep(1);
    }
}
