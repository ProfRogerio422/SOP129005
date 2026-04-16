#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>

int main() {
    mqd_t mq; // descritor da fila de mensagens
    char *msg = "Olá do processo emissor!";
    
    // Abre a fila (Cria se não existir)
    // /minha_fila é o nome (deve começar com /)
    mq = mq_open("/minha_fila", O_CREAT | O_WRONLY, 0644, NULL);

    // Se o Sistema Operacional não conseguir criar a fila (por falta de memória, nome inválido ou falta de permissão), ele não tem um número positivo para te dar.
    if (mq == (mqd_t)-1) {  // -1: Erro critico
        perror("Erro no mq_open");
        exit(1);
    }

    // Envia a mensagem (prioridade 1)
    if (mq_send(mq, msg, strlen(msg) + 1, 1) == -1) {
        perror("Erro no mq_send");
    } else {
        printf("Mensagem enviada com sucesso!\n");
    }

    mq_close(mq);
    return 0;
}
