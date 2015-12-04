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
    push(13);
    while(finish != 0) {
        printf("%d ", path[finish]);
        push(path[finish]);
        finish = path[finish];
    }
    printf("\n");
    while(top != -1) {
        int start = pop();
        int dest = TOP();
        int temp = robo_state - dir[start][dest];
        if(temp == 0) {
            printf("F -");
            //robo_state = F;
        }
        else if(temp == -2 || temp == 2) {
            printf("B -");
            robo_state -= -2;
            if(robo_state < 0)
                robo_state += 4;
        }
        else if(temp == 1 || temp == -3) {
            printf("L -");
            robo_state--;
            if(robo_state == 0)
                robo_state += 4;
        }
        else if(temp == -1 || temp == 3) {
            printf("R -");
            robo_state++;
            if(robo_state == 5)
                robo_state = 1;
        }
        else {
            printf(" (ERROR : %d) -", temp);
        }
        //printf("%d - ", temp);
        if(TOP() == 13)
            break;
    }
    printf("\n");
    return 0;
}
