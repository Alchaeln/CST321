#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>

int MAX = 100;
int WAKEUP = SIGUSR1;
int SLEEP = SIGUSR2;
pid_t otherPid;
sigset_t sigset;

//buffer
struct CIRCULAR_BUFFER
{
    int count;
    int lower;
    int upper;
    int buffer[100];
};

struct CIRCULAR_BUFFER *buffer = NULL;

void MySigHandler (int sig)
{
    if(sig == SIGUSR1)
    {
        printf("Caught SIGURS1\n");
    }
}

//sleeps and waits
void sleepAndWait()
{
    int nSig;

    printf("Sleeping......\n");
    sigwait(&sigset, &nSig);
    printf("Awoken\n");
}

void wakeupOther()
{
    kill(otherPid, WAKEUP);
}

void getValue()
{
    printf("Read %d from buffer\n",buffer->buffer[buffer->upper]);
    buffer->upper++;
    buffer->count--;
}

void putValue (struct CIRCULAR_BUFFER* buffer, int value)
{
    printf("Wrote %d to buffer\n", value);
    buffer->buffer[buffer->lower] = value;
    buffer->lower++;
    buffer->count++;
}

void consumer()
{
    //consumer is sleeping
    printf("Running Consumer Process....\n");
    sleepAndWait();
    //consumes 200 times
    for(int x = 0; x<205; x++)
    {
        getValue();
        //if no values written, go to bed
        if(buffer->count == 0)
        {
            wakeupOther();
            sleepAndWait();
        }
    }

    _exit(1);
}

void producer()
{
    printf("Producer Process running....\n");
    //produces 200 vals
    for(int x = 0; x<205; x++)
    {
        putValue(buffer, x);
        //if 5 vals have been made without being consumed wake up consumer and go to bed
        if(buffer->count == 5)
        {
            wakeupOther();
            sleepAndWait();
        }
    }
_exit(1);
}

int main(int argc, char* argv[])
{
    signal(SIGUSR1, &MySigHandler);
    sigemptyset(&sigset);
    sigaddset(&sigset, WAKEUP);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    pid_t pid;
    buffer = (struct CIRCULAR_BUFFER*)mmap(0, sizeof(buffer), PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    buffer->count = 0;
    buffer->lower = 0;
    buffer->upper = 0;

    pid = fork();
    if(pid == -1)
    {
        printf("Can't fork, error %d\n", errno);
        exit(EXIT_FAILURE);
    }
    
    if(pid == 0)
    {
        otherPid = getppid();
        producer();
    }

    else
    {
        otherPid = pid;
        consumer();
    }
    return 0;
}