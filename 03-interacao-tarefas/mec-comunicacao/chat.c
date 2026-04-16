#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define QUEUE_NAME  "/chat_prioridade"
#define MAX_SIZE    1024

int main() {
    mqd_t mq;
    struct mq_attr attr;
    pid_t pid;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;

    mq_unlink(QUEUE_NAME); 
    mq = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0644, &attr);

    pid = fork();

    if (pid == 0) { // FILHO
        char *mensagens[] = {"Msg 1", "Msg 2", "SHUTDOWN", "Msg 4"};
        int prioridades[] = {1, 1, 10, 1};

        for (int i = 0; i < 4; i++) {
            printf("[Filho] Enviando: %s (Prio: %d)\n", mensagens[i], prioridades[i]);
            mq_send(mq, mensagens[i], strlen(mensagens[i]) + 1, prioridades[i]);
        }
        printf("[Filho] Todas as mensagens foram enviadas!\n");
        exit(0);
    } 
    else { // PAI
        char buffer[MAX_SIZE];
        unsigned int prio;

        printf("[Pai] Dormindo 2s para a fila encher...\n");
        sleep(2); // O segredo está aqui!

        printf("[Pai] Começando a ler agora:\n");
        for (int i = 0; i < 4; i++) {
            mq_receive(mq, buffer, MAX_SIZE, &prio);
            printf("[Pai] Recebido: '%s' (Prio detectada: %d)\n", buffer, prio);
        }

        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        wait(NULL);
    }
    return 0;
}
