#ifndef DIJKSTRA__H_
#define DIJKSTRA__H_
#include <stdio.h>

#define F 1 //Foward
#define R 2 //Right
#define B 3 //Back
#define L 4 //Left

typedef struct NODE {
    int a;
    int b;
}Node;

int map[14][14];//map
int dir[14][14];//인접 노드의 방향
int visited[14];////
int path[14];////
int d[14];
int robo_state_t;//robo_car의 진행 방향

int stack_t[15];
int top_t;
int top_cut;
Node CUT[10];//끊어진 길 저장
//막힌 경우 a와 b로 표시 -> 999로 설정
//현재 위치는 x와 y로 표시
void init(int flag, int a, int b);

void dijkstra(int start);

//simple stack

void push_(int n);
int pop_();
int TOP_();

#endif
