#include<stdio.h>
#include "test.h"

int main() {
    int t_start = 0;
    init(0, 0, 0);
    dijkstra(t_start);
    int finish = 13;
    int i;
    int flag = 1;
    for(i=0;i<14;i++)
        printf("%d ",path[i]);
    printf("\n");
    for(i=0;i<14;i++)
         printf("4 ~ %d : %d\n",i,d[i]);
    printf("13 ");
    push(13);
    while(finish != t_start) {
        printf("%d ", path[finish]);
        push(path[finish]);
        finish = path[finish];
    }
    printf("\n");
    while(top != -1) {
        int start = pop();
        int dest = TOP();
        int temp = robo_state - dir[start][dest];
        //printf("===== START : %d ===== DEST : %d\n", start, dest);
/*
        // 끊어진 상황 시뮬레이션
        if(start == 8 && dest == 13 && flag == 1) {
            flag = 0;
            while(top == -1)
                pop();
            printf("B\n");
            //printf("### state : %d ###", robo_state);
            robo_state -= 2;
            if(robo_state < 0)
                robo_state += 4;

            init(1, start, dest, 0, 0);
            dijkstra(start);
            for(i=0;i<14;i++)
                printf("0 ~ %d : %d\n",i,d[i]);
            push(13);
            finish = 13;
            while(finish != start) {
                printf("%d ", path[finish]);
                push(path[finish]);
                finish = path[finish];
            }
            continue;
        }
        //시뮬
       */
        if(temp == 0) {
            printf("F -");
            //robo_state = F;
        }
        else if(temp == -2 || temp == 2) {
            printf("B -");
            robo_state -= 2;
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
