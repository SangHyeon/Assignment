#include<stdio.h>

#define F 1 //Foward
#define R 2 //Right
#define B 3 //Back
#define L 4 //Left

int map[14][14];//map
int dir[14][14];//인접 노드의 방향
int visited[14] = {0, };
int path[14] = {0, };
int d[14];
int robo_state = F;//robo_car의 진행 방향

int stack[15] ={0, };
int top = -1;

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
    map[0][1] = map[1][0] = 45;
    map[1][2] = map[2][1] = 95;
    map[2][3] = map[3][2] = 48;
    map[2][4] = map[4][2] = 48;
    map[3][5] = map[5][3] = 70;
    map[4][6] = map[6][4] = 70;
    map[5][7] = map[7][5] = 48;
    map[6][7] = map[7][6] = 48;
    map[5][8] = map[8][5] = 48;
    map[7][9] = map[9][7] = 35;
    map[9][10] = map[10][9] = 22;
    map[10][11] = map[11][10] = 35;
    map[5][12] = map[12][5] = 70;
    map[8][13] = map[13][8] = 70;
    map[11][12] = map[12][11] = 70;
    map[12][13] = map[13][12] = 48;

    //해당 위치에서 다음 위치로 이동하는 방향
    //robo_car 방향 - 가려는 방향 
    // 0 : F // -2 or 2 : B // 1 or -3 : L // -1 or 3 : R
    dir[0][1] = F; dir[1][0] = B;
    dir[1][2] = L; dir[2][1] = R;
    dir[2][3] = F; dir[3][2] = B;
    dir[2][4] = B; dir[4][2] = F;
    dir[3][5] = L; dir[5][3] = R;
    dir[4][6] = L; dir[6][4] = R;
    dir[5][7] = B; dir[7][5] = F;
    dir[6][7] = F; dir[7][6] = B;
    dir[5][8] = F; dir[8][5] = B;
    dir[7][9] = L; dir[9][7] = R;
    dir[9][10] = B; dir[10][9] = F;
    dir[10][11] = L; dir[11][10] = R;
    dir[5][12] = L; dir[12][5] = R;
    dir[8][13] = L; dir[13][8] = R;
    dir[11][12] = F; dir[12][11] = B;
    dir[12][13] = F; dir[13][12] = B;


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
    while(1) {
        int k;
        int count = 0;
        for(k=0; k<14; k++)
            if(visited[k] != 0)
                count++;
        if(count == 14)
            break;
        for(i=0; i<14; i++) {
            min = 99999;
            for(j=0; j<14; j++) {
                if(min > d[j] && visited[j] == 0) {
                    min = d[j];//map[i][j];
                    cur_position = j;
                }
            }
        }
        visited[cur_position] = 1;
        for(j=0; j<14; j++) {
            if (d[j] > map[cur_position][j]+d[cur_position] \
                    && map[cur_position][j] != 9999) { 
                d[j] = map[cur_position][j] + d[cur_position];
                printf("&&&&&&&&&&&&&&\n");
                printf("CUR POS : %d\n", cur_position);
                path[j] = cur_position;
            } 
        }
    }
}

//simple stack
void push(int n) {
    top++;
    stack[top] = n;
}
int pop() {
    top--;
    return stack[top+1];
}
int TOP() {
    return stack[top];
}
