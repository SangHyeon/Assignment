#include<stdio.h>
#include "test.h"

int main() {
    init(0, 0, 0, 0, 0);
    dijkstra(0);
    int finish = 13;
    int i;
    for(i=0;i<14;i++)
         printf("0 ~ %d : %d\n",i,d[i]);
    printf("13 "); 
    while(finish != 0) {
        printf("%d ", path[finish]);
        finish = path[finish];
    }
    printf("\n");
    return 0;
}
