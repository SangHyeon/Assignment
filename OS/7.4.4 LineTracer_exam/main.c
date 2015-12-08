/*********************************************************
    적외선 센서를 이용한 라인트레이서 예제 프로그램
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "uart_api.h"
#include "robot_protocol.h"
#include "keyboard.h"
#include "dijkstra.h"


int main()
{
    ////////////////////////////////////////////////
    int start_pos=0;
    int ret;
    int r_turn = 0;
    int l_turn = 0;
    int finish = 13;
    int i;
    int start_;
    int dest_;
    int direction_;
    int temp_robo_state_t=0;
    init(0, 0, 0);
    dijkstra(start_pos);
    push_(13);
    while(finish != start_pos) {
        push_(path[finish]);
        finish = path[finish];
    }
    //sleep(3);
    ////////////////////////////////////////////////
    unsigned char Line_Value,tmp_line=0xff;

    ret = user_uart1_open("SAC1");

    if (ret < 0)
    {
        printf("\n UART1 Open error!");
        exit(0);
    }

    user_uart1_config(115200, 8, UART_PARNONE, 1);

    init_keyboard();

    printf("**************************\n");
    printf(" RoboCAR Linetracer exam\n");
    printf("**************************\n");

    RoboCAR_AllMotor_Control(STOP,0);
    
    ///////////////////////////////////////////////////
    pop_();//일단 맨 처음 부분 삭제(어차피 직진)
    /*
    start_ = pop_();
    dest_ = TOP_();
    direction_ = robo_state_ - dir[start_][dest_];
    */
    //////////////////////////////////////////////////

    while(1)
    {
        if(kbhit()) break;

        usleep(5*1000);

        Line_Value= RoboCAR_Get_InfraredRay_Data();

        //printf("InfraredRay = 0x%x\n",Line_Value);

        if(tmp_line == Line_Value) continue;

        tmp_line = Line_Value;

        switch(Line_Value){
            //전진
            case 0xE7:  // 1110 0111
            case 0xEF:  // 1110 1111
            case 0xF7:  // 1111 0111
            case 0xC7:  // 1100 0111
            //case 0xC3:  // 1100 0011
                if(l_turn) {
                    usleep(50*1000);
                    RoboCAR_Move_Angle(3, 90, 88);
                    usleep(2000*1000);
                    l_turn = 0;
                    break;
                }
                else if(r_turn) {
                    usleep(50*1000);
                    printf("&&&&&&&&&&&&&&&\n");
                    RoboCAR_AllMotor_Control(STOP,0);
                    RoboCAR_Move_Angle(4, 90, 80);
                    usleep(2000*1000);
                    r_turn = 0;
                    printf("###############\n");
                    break;
                }
                printf("go ");
                RoboCAR_AllMotor_Control(FORWARD,50);
            break;

            //좌회전
            case 0xF3: //1111 0011
            case 0xFB: //1111 1011
            case 0xF9: //1111 1001
                RoboCAR_LeftMotor_Control(FORWARD,40);
                RoboCAR_RightMotor_Control(FORWARD,60);
                usleep(130*1000);
                if(l_turn) {
                    //usleep(50*1000);
                    RoboCAR_Move_Angle(3, 90, 88);
                    usleep(2000*1000);
                    l_turn = 0;
                    //break;
                }
                else if(r_turn) {
                    //usleep(50*1000);
                    printf("SHIT\n");
                    printf("&&&&&&&&&&&&&&&\n");
                    RoboCAR_AllMotor_Control(STOP,0);
                    RoboCAR_Move_Angle(4, 90, 80);
                    usleep(2000*1000);
                    r_turn = 0;
                    printf("###############\n");
                    //break;
                }
                //RoboCAR_LeftMotor_Control(FORWARD,40);
                //RoboCAR_RightMotor_Control(FORWARD,60);
            break;

            //left turn angle
            case 0xC0: // 1100 0000
            case 0xE0: // 1110 0000
            case 0xF0: // 1111 0000
                start_ = pop_();
                dest_ = TOP_();
                direction_ = robo_state_t - dir[start_][dest_];
                printf("START :  %d  DEST :  %d\n", start_, dest_);
                if(direction_ == 0) {
                    //printf("FRONT\n");
                    printf("ERROR!!!****\n");
                    //sleep(3);
                }
                else if(direction_ == -2 || direction_ == 2) {
                    printf("ERROR!!!\n");
                    //sleep(3);

                    robo_state_t -=2;
                    if(robo_state_t < 0)
                        robo_state_t += 4;
                }
                else if(direction_ == 1 || direction_ == -3) {
                    robo_state_t--;
                    if(robo_state_t == 0)
                        robo_state_t += 4;
                    l_turn = 1;
                    printf("LEFT\n");
                }
                else if(direction_ == -1 || direction_ == 3) {
                    robo_state_t++;
                    if(robo_state_t == 5)
                        robo_state_t = 1;
                    r_turn = 1;
                    printf("ERROR!!!****\n");
                    //sleep(3);
                }
                else {
                    printf("ERROR!!!****\n");
                    //sleep(3);
                }
                //RoboCAR_LeftMotor_Control(BACKWARD, 70);
                //RoboCAR_RightMotor_Control(FORWARD, 80);
                RoboCAR_AllMotor_Control(FORWARD, 50);
                //l_turn = 1;
                //RoboCAR_Move_Angle(3, 80, 90);
                //usleep(300*1000);
                usleep(230*1000);
            break;

            //우측으로 후진
            case 0xFC: // 1111 1100
            case 0xFD: // 1111 1101
            case 0xFE: // 1111 1110
                RoboCAR_LeftMotor_Control(BACKWARD,60);
                RoboCAR_RightMotor_Control(BACKWARD,40);
            break;

            //우회전
            case 0xCF: // 1100 1111
            case 0xDF: // 1101 1111
            case 0x9F: // 1001 1111
                RoboCAR_LeftMotor_Control(FORWARD,60);
                RoboCAR_RightMotor_Control(FORWARD,40);
                usleep(130*1000);
                if(l_turn) {
                    //usleep(10*1000);
                    RoboCAR_AllMotor_Control(STOP,0);
                    RoboCAR_Move_Angle(3, 90, 88);
                    usleep(2000*1000);
                    l_turn = 0;
                    //break;
                }
                else if(r_turn) {
                    //usleep(10*1000);
                    printf("SHIT\n");
                    printf("&&&&&&&&&&&&&&&\n");
                    RoboCAR_AllMotor_Control(STOP,0);
                    RoboCAR_Move_Angle(4, 90, 80);
                    usleep(1200*1000);
                    r_turn = 0;
                    printf("###############\n");
                    //break;
                }
                //RoboCAR_LeftMotor_Control(FORWARD,60);
                //RoboCAR_RightMotor_Control(FORWARD,40);
            break;

            //right turn angle
            case 0x03: // 0000 0011
            case 0x07: // 0000 0111
            case 0x0F: // 0000 1111
                start_ = pop_();
                dest_ = TOP_();
                direction_ = robo_state_t - dir[start_][dest_];
                printf("START :  %d  DEST :  %d\n", start_, dest_);
                if(direction_ == 0) {
                    //printf("FRONT\n");
                    printf("ERROR!!!****\n");
                    //sleep(3);
                }
                else if(direction_ == -2 || direction_ == 2) {
                    printf("ERROR!!!\n");
                    //sleep(3);

                    robo_state_t -=2;
                    if(robo_state_t < 0)
                        robo_state_t += 4;
                }
                else if(direction_ == 1 || direction_ == -3) {
                    robo_state_t--;
                    if(robo_state_t == 0)
                        robo_state_t += 4;
                    l_turn = 1;
                    printf("ERROR!!!****\n");
                    //sleep(3);
                }
                else if(direction_ == -1 || direction_ == 3) {
                    robo_state_t++;
                    if(robo_state_t == 5)
                        robo_state_t = 1;
                    r_turn = 1;
                    printf("RIGHT\n");
                }
                else {
                    printf("ERROR!!!****\n");
                    //sleep(3);
                }
                //RoboCAR_LeftMotor_Control(FORWARD, 80);
                //RoboCAR_RightMotor_Control(BACKWARD, 70);
                //RoboCAR_AllMotor_Control(FORWARD, 35);
                //RoboCAR_Move_Angle(4, 80, 90);
                RoboCAR_AllMotor_Control(FORWARD, 50);
                //r_turn = 1;
                //usleep(300*1000);
                usleep(230*1000);
            break;

            case 0x00: // 0000 0000 //갈림길일 때
            case 0x81: // 1000 0001
                printf("+ or -\n");
                start_ = pop_();
                dest_ = TOP_();
                printf("START :  %d  DEST :  %d\n", start_, dest_);
                direction_ = robo_state_t - dir[start_][dest_];
                if(direction_ == 0) {
                    printf("FRONT\n");
                }
                else if(direction_ == -2 || direction_ == 2) {
                    printf("ERROR!!!\n");
                    //sleep(3);

                    robo_state_t -=2;
                    if(robo_state_t < 0)
                        robo_state_t += 4;
                }
                else if(direction_ == 1 || direction_ == -3) {
                    robo_state_t--;
                    if(robo_state_t == 0)
                        robo_state_t += 4;
                    l_turn = 1;
                    printf("LEFT 2 \n");
                    RoboCAR_AllMotor_Control(FORWARD, 50);
                    usleep(200*1000);
                    break;
                }
                else if(direction_ == -1 || direction_ == 3) {
                    robo_state_t++;
                    if(robo_state_t == 5)
                        robo_state_t = 1;
                    r_turn = 1;
                    printf("RIGHT 2 \n");
                    RoboCAR_AllMotor_Control(FORWARD, 50);
                    usleep(200*1000);
                    printf("*******************\n");
                    break;
                }
                else {
                    printf("ERROR!!!****\n");
                    //sleep(3);
                }
                ////RoboCAR_AllMotor_Control(FORWARD, 50);
                //usleep(300*1000);
                ////usleep(200*1000);
            break;

            //좌측으로 후진
            case 0x3F: //0011 1111
            case 0xBF: //1011 1111
            case 0x7F: //0111 1111
                RoboCAR_LeftMotor_Control(BACKWARD,40);
                RoboCAR_RightMotor_Control(BACKWARD,60);
            break;

            // 정지
            case 0xFF:
                if(top_t == -1) { //목표 지점 도착
                    RoboCAR_AllMotor_Control(STOP,0);
                    break;
                }
                
                if(l_turn) {
                    //usleep(200*1000);
                    RoboCAR_Move_Angle(3, 90, 85);
                    usleep(2000*1000);
                    l_turn = 0;
                }
                else if(r_turn) {
                    //usleep(200*1000);
                    RoboCAR_Move_Angle(4, 90, 80);
                    usleep(2000*1000);
                    r_turn = 0;
                }
                else {
                    RoboCAR_AllMotor_Control(STOP,0);
                    printf("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n");
                    RoboCAR_Move_Angle(3, 90, 180);
                    usleep(3000*1000);

                    r_turn = 0;
                    l_turn = 0;
                    //robo_state_t -=2;
                    //if(robo_state_t < 0)
                    //    robo_state_t += 4;
                    printf("--------- %d   ,  %d ------------\n", direction_, robo_state_t);
                    
                    if(direction_ == 1 || direction_ == -3) {
                        robo_state_t += 2;
                        if(robo_state_t >= 5)
                            robo_state_t = 1;
                        printf("teststetsetsetsetsetsets\n");
                    }
                    else if(direction_ == -1 || direction_ == 3) {
                        robo_state_t -= 2;
                        if(robo_state_t <= 0)
                            robo_state_t += 4;
                        printf("te***ststetsetsetsetsetsets\n");
                    }

                    temp_robo_state_t = robo_state_t;
                    
                    top_t = -1;
                    init(1, start_, dest_);
                    robo_state_t = temp_robo_state_t;
                    printf("--------- %d   ,  %d ------------\n", direction_, robo_state_t);
                    printf("===========> START : %d \n", start_);
                    start_pos = start_;
                    dijkstra(start_pos);
                    push_(13);
                    finish = 13;
                    while(finish != start_pos) {
                        push_(path[finish]);
                        finish = path[finish];
                    }
                }
            break;
        }// end switch


    }//end while

    RoboCAR_AllMotor_Control(STOP,0);

    user_uart1_close();
    close_keyboard() ;

    return 0;
}
