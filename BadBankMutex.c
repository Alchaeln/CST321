#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_DEPOSITS 1000000

int balance = 0;
int depositAmount = 1;

pthread_mutex_t mutex;

void *deposit(void *a)
{
    int x, tmp;
    for(x = 0; x < MAX_DEPOSITS; ++x)
    {
        pthread_mutex_lock(&mutex);

        tmp = balance;
        tmp = tmp + 1;
        balance = tmp;

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_t tid1, tid2;

    if(pthread_create(&tid1, NULL, deposit, NULL))
    {
        printf("\n ERROR creating deposit thread 1");
        exit(1);
    }

    if(pthread_create(&tid2, NULL, deposit, NULL))
    {
        printf("\n ERROR creating deposit thread 2");
        exit(1);
    }

    if(pthread_join(tid1,NULL))
    {
        printf("\n ERROR joining deposit thread 1");
        exit(1);
    }

    if(pthread_join(tid2,NULL))
    {
        printf("\n ERROR joining deposit thread 2");
        exit(1);
    }

    if(balance < 2 * MAX_DEPOSITS)
        printf("\n BAD BALANCE: bank balance is $%d and should be $%d\n", balance, 2 * MAX_DEPOSITS);
    else
        printf("\n GOOD BALANCE: bank balance is $%d\n", balance);
        
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
}