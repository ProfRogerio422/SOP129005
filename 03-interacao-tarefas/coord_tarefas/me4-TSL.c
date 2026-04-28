#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS  100
#define NUM_STEPS 100000

int sum  = 0 ;
int lock = 0 ;

// Protocolo de entrada: Seção Crítica
void enter_cs (int *lock)
{
    // Operação Atômica: tenta colocar o bit 1.
    // Se o retorno for 1, significa que já estava ocupado (true), então continua no while.
    // Se o retorno for 0, significa que pegou o lock, então sai do loop.
    while (__sync_fetch_and_or (lock, 1)) ;   // busy waiting
}

// Protocolo de saída: Seção Crítica
void leave_cs (int *lock)
{
    (*lock) = 0 ;
}

void *threadBody(void *id)
{
    int i ;

    for (i=0; i < NUM_STEPS; i++)
    {
        enter_cs (&lock) ;
        sum += 1 ;   // seção crítica protegida por hardware
        leave_cs (&lock) ;
    }

    pthread_exit (NULL) ;
}

int main (int argc, char *argv[])
{
    pthread_t thread [NUM_THREADS] ;
    long i;
    long expected = (long)NUM_THREADS * NUM_STEPS;

    // Criando as threads
    for(i=0; i < NUM_THREADS; i++)
    {
        if (pthread_create (&thread[i], NULL, threadBody, (void *) i))
        {
            perror ("pthread_create") ;
            exit (1) ;
        }
    }
    
    // Aguardando todas terminarem
    for (i=0; i < NUM_THREADS; i++)
    {
        pthread_join (thread[i], NULL) ;
    }

    printf ("--- Resultado: Algoritmo TSL (Base Maziero) ---\n") ;
    printf ("Valor esperado: %ld\n", expected) ;
    printf ("Valor obtido:   %d\n", sum) ;
    printf ("Diferenca:      %ld\n", expected - sum) ;

    return 0 ;
}