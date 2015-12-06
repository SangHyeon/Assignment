/*********************************************************
    적외선 센서를 이용한 라인트레이서 예제 프로그램
**********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "uart_api.h"
#include "robot_protocol.h"
#include "keyboard.h"
//#include "test.h"
#include "dijkstra.h"


int main()
{
    int ret;
    int r_turn = 0;
    int l_turn = 0;

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

    while(1)
    {
        if(kbhit()) break;

        usleep(10*1000);

        Line_Value= RoboCAR_Get_InfraredRay_Data();

        printf("InfraredRay = 0x%x\n",Line_Value);

        if(tmp_line == Line_Value) continue;

        tmp_line = Line_Value;

        switch(Line_Value){

            //전진
            case 0xE7:  // 1110 0111
            case 0xEF:  // 1110 1111
            case 0xF7:  // 1111 0111
                RoboCAR_AllMotor_Control(FORWARD,50);
            break;

            //좌회전
            case 0xF3: //1111 0011
            case 0xFB: //1111 1011
            case 0xF9: //1111 1001
                RoboCAR_LeftMotor_Control(FORWARD,40);
                RoboCAR_RightMotor_Control(FORWARD,60);
            break;

            //left turn angle
            case 0xC0: // 1100 0000
            case 0xE0: // 1110 0000
            case 0xF0: // 1111 0000
                //RoboCAR_LeftMotor_Control(BACKWARD, 70);
                //RoboCAR_RightMotor_Control(FORWARD, 80);
                RoboCAR_AllMotor_Control(FORWARD, 50);
                l_turn = 1;
                //RoboCAR_Move_Angle(3, 80, 90);
                usleep(300*1000);
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
            break;

            //right turn angle
            case 0x03: // 0000 0011
            case 0x07: // 0000 0111
            case 0x0F: // 0000 1111
                //RoboCAR_LeftMotor_Control(FORWARD, 80);
                //RoboCAR_RightMotor_Control(BACKWARD, 70);
                //RoboCAR_AllMotor_Control(FORWARD, 35);
                //RoboCAR_Move_Angle(4, 80, 90);
                RoboCAR_AllMotor_Control(FORWARD, 50);
                r_turn = 1;
                usleep(300*1000);
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
                if(l_turn) {
                    RoboCAR_Move_Angle(3, 100, 95);
                    usleep(2000*1000);
                    l_turn = 0;
                }
                else if(r_turn) {
                    RoboCAR_Move_Angle(4, 100, 95);
                    usleep(2000*1000);
                    r_turn = 0;
                }
                else
                    RoboCAR_AllMotor_Control(STOP,0);
            break;
        }// end switch


    }//end while

    RoboCAR_AllMotor_Control(STOP,0);

    user_uart1_close();
    close_keyboard() ;

    return 0;
}
