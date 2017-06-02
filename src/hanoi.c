#include <stdio.h>
#include <stdlib.h>

static int count = 0;

void hanoi (int n,int d){
    if(n == 0 ) return;
    hanoi(n-1,-d);
    count++;
    hanoi(n-1,+d);
}

int main (int arc,char** argv){
    int n = atoi(argv[1]);
    hanoi(n,1);
    printf("%d\n",count);
    return 0;
}
