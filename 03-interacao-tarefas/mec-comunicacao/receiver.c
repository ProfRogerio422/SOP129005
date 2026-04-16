#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>

int main() {
    mqd_t mq;
    struct mq_attr attr;
    char buffer[1024];

    // Abre a fila existente
    mq = mq_open("/minha_fila", O_RDONLY);    

    // Se o Sistema Operacional não conseguir criar a fila (por falta de memória, nome inválido ou falta de permissão), ele não tem um número positivo para te dar.
    if (mq == (mqd_t)-1) {
        perror("Erro no mq_open");
        exit(1);
    }

    // Obtém atributos para saber o tamanho máximo da mensagem
    mq_getattr(mq, &attr);

    // Recebe a mensagem
    ssize_t bytes_read = mq_receive(mq, buffer, attr.mq_msgsize, NULL);
    
    if (bytes_read >= 0) {
        printf("Mensagem recebida: %s\n", buffer);
    } else {
        perror("Erro no mq_receive");
    }

    mq_close(mq);
    mq_unlink("/minha_fila"); // Remove a fila do sistema
    return 0;
}
