#include<stdio.h>

int map[14][14];
int visited[14] = {0, };
int path[14] = {0, };
int d[14];

//막힌 경우 a와 b로 표시 -> 999로 설정
//현재 위치는 x와 y로 표시
void init(int flag, int a, int b, int x, int y) {
    int i, j;
    for(i=0;i<14;i++) {
        d[i] = 9999;
        for(j=0;j<14;j++)
            map[i][j] = 9999;
    }
    //map 초기화
    map[0][1] = map[1][0] = 45;//w
    map[1][2] = map[2][1] = 95;//l
    map[2][3] = map[3][2] = 48;//r
    map[2][4] = map[4][2] = 48;//l
    map[3][5] = map[5][3] = 70;//l
    map[4][6] = map[6][4] = 70;//r
    map[5][7] = map[7][5] = 48;//5->7 : l , 7-> 5 : w
    map[6][7] = map[7][6] = 48;//r
    map[5][8] = map[8][5] = 48;//3-5-8:r, 7-5-8:w
    map[7][9] = map[9][7] = 35;//
    map[9][10] = map[10][9] = 22;//
    map[10][11] = map[11][10] = 35;//
    map[5][12] = map[12][5] = 70;//
    map[8][13] = map[13][8] = 70;//
    map[11][12] = map[12][11] = 70;//
    map[12][13] = map[13][12] = 48;//

    if(flag) {
        map[a][b] = map [b][a] = 9999;
    }
    for(i=0;i<14;i++) {
        for(j=0;j<14;j++) {
            if(map[i][j] == 9999)
                printf("-- ");
            else
                printf("%d ", map[i][j]);
        }
        printf("\n");
    }
}

void dijkstra(int start) {
    d[start] = 0;
    int min;
    int cur_position;
    int i, j;
    for(i=0; i<14; i++) {
        min = 99999;
        for(j=0; j<14; j++) {
            if(min > d[i] && visited[j] == 0) {
                min = map[i][j];
                cur_position = j;
            }
        }
        visited[cur_position] = 1;
        for(j=0; j<14; j++) {
             if (d[j] > map[cur_position][j]+d[cur_position] \
                     && map[cur_position][j] != 9999) { 
                d[j] = map[cur_position][j] + d[cur_position];
                path[j] = cur_position;
             } 
        }
    }
}

/*int main() {
    init(0, 0, 0, 0, 0);
    dijkstra(0);
    int finish = 13;
    for(int i=0;i<14;i++)
         printf("0 ~ %d : %d\n",i,d[i]);
    printf("13 "); 
    while(finish != 0) {
        printf("%d ", path[finish]);
        finish = path[finish];
    }
    printf("\n");
    return 0;
}*/
