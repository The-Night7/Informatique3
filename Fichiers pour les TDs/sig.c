#include<stdio.h>
#include<signal.h>
#include<unistd.h>
  
void handle(int sig)
{
    printf("Caught signal %d\n", sig);
}
  
int main()
{
    // local variable
    int n = 0;
    // Define handler for each signal
    // (here we have the same handler)
    signal(SIGINT , handle);
    while (1) {
        printf("[sig.c] %d seconds \n", n++);
        sleep(1);
    }
    printf("[END of program]");
    return 0;
}

