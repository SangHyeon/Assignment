#include<iostream>
#include<cwchar>
#include<clocale>
using namespace std;

//Simple Queue
wchar_t que[100001];
int front=1,rear=1;
void eq(wchar_t s) {
    que[rear] = s;
    rear++;
    rear%=100001;
}

wchar_t dq() {
    int temp = front;
    front++;
    front%=100001;
    return que[temp];
}
void printBuff() {
    while(rear != front)
        putwchar(dq());
    wprintf(L"/");    
}
//{"ㄱ", "ㄴ", "ㄷ", "ㅁ", "ㅂ", "ㅅ", "ㅇ", "ㅈ", "ㅊ", "ㅋ", "ㅌ", "ㅍ", "ㅎ"};
//j : 12593 12596 12599 12601 12609 12610 12613 12615 12616 12618 12619 12620 12621 12622
//j : 12593 ~ 12622
//m : 12623 ~ 12643
//WEOF : 10
//o : another

int main() {
    setlocale(LC_ALL,"");

    wchar_t s;
    int state = 1;//{ q0 = 1, j = 2, jm = 3, jmj = 4, jmm = 5, jnxj = 6 }
    while((s = getwchar()) != WEOF) {
        switch(state) {
            case 1:
                if(s >= 12593 && s <= 12622) {
                    eq(s);
                    state = 2;//j
                }
                else if((s >= 32 && s <= 126) || s == 10){
                    putwchar(s);
                    state = 1;
                }
                else {
                    cout<<"ERROR!"<<endl;//m
                    putwchar(s);
                }
                break;
            case 2:
                if((s >= 32 && s <= 126) || s == 10) {
                    printBuff();
                    putwchar(s);
                    state = 1;//q0
                }
                else if(s >= 12623 && s <= 12643){
                    eq(s);
                    state = 3;//jm
                }
                else {
                    cout<<"ERROR!!"<<endl;
                    putwchar(s);
                }
                break;
            case 3:
                if((s >= 32 && s <= 126) || s == 10) {
                    printBuff();
                    putwchar(s);
                    state = 1;//q0
                }
                else if(s >= 12593 && s <= 12622) {
                    eq(s);
                    state = 4;//jmj
                }
                else if(s >= 12623 && s <= 12643) {
                    eq(s);
                    state = 5;//jmm
                }
                else {
                    cout<<"EROOR!!!"<<endl;
                    putwchar(s);
                }
                break;
            case 4://jmj
                if((s >= 32 && s <= 126) || s == 10) {
                    printBuff();
                    putwchar(s);
                    state = 1;//q0
                }
                else if(s >= 12593 && s <= 12622) {
                    eq(s);
                    state = 6;
                }
                else if(s >= 12623 && s <= 12643) {
                    putwchar(dq());
                    putwchar(dq());
                    //print |
                    wprintf(L"/");
                    eq(s);
                    state = 3;//jm
                }
                else {
                    cout<<"ERROR!!!!"<<endl;
                    putwchar(s);
                }
                break;
            case 5://jmm
                if((s >= 32 && s <= 126) || s == 10) {
                    printBuff();
                    putwchar(s);
                    state = 1;
                }
                else if(s >= 12593 && s <= 12622) {
                    eq(s);
                    state = 6;
                }
                else {
                    cout<<"ERROR!!!!!"<<endl;
                    putwchar(s);
                }
                break;
            case 6://jnxj
                if((s >= 32 && s <= 126) || s == 10) {
                    printBuff();
                    putwchar(s);
                    state = 1;//2???
                }
                else if(s >= 12593 && s <= 12622) {
                    printBuff();
                    eq(s);
                    state = 2;
                }
                else if(s >= 12623 && s <= 12643) {
                    putwchar(dq());
                    putwchar(dq());
                    putwchar(dq());
                    wprintf(L"/");
                    eq(s);
                    state = 3;
                }
                else {
                    cout<<"ERORR!!!!!!"<<endl;
                    putwchar(s);
                }
                break;
        }

    }
    while(rear!=front) 
        putwchar(dq());
    return 0;
}
