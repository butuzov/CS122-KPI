#include <stdio.h>
#include <sys/time.h>

int main(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long int ms = tp.tv_sec;
    printf("%09ld.%06i", ms, tp.tv_usec);
}
