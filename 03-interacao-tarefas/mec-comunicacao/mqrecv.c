// Arquivo mqrecv.c: recebe mensagens de uma fila de mensagens POSIX.
// Em Linux, compile usando: cc -Wall mqrecv.c -o mqrecv -lrt
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>   // necessário para O_CREAT, O_RDWR

#define QUEUE "/my_queue"

int main (int argc, char *argv[])
{
    mqd_t queue;           // descritor da fila de mensagens
    struct mq_attr attr;   // atributos da fila de mensagens
    int msg;               // as mensagens são números inteiros

    // define os atributos da fila de mensagens
    attr.mq_maxmsg = 10;              // capacidade para 10 mensagens  (aguenta até 10 números por vez)
    attr.mq_msgsize = sizeof(msg);    // tamanho de cada mensagem
    attr.mq_flags = 0;
    
    // Remove a fila do sistema
    if (mq_unlink(QUEUE) == -1) {
        perror("mq_unlink");
    }
    

    // abre ou cria a fila com permissões 0666
    if ((queue = mq_open(QUEUE, O_RDWR | O_CREAT, 0666, &attr)) < 0)
    {
        
        perror("mq_open");
        exit(1);
    }

    // recebe cada mensagem e imprime seu conteúdo
    for (;;)   {
    
        printf("Aguardando mensagem...\n"); // Avisa antes de bloquear
        sleep(1);

        // Bloqueio: Quando o programa chega nesta linha, ele para e dorme.
        if ((mq_receive(queue, (void*) &msg, sizeof(msg), 0)) < 0)
        {
            perror("mq_receive");
            exit(1);
        }
        printf("Received msg value %d\n", msg);
    }
}
