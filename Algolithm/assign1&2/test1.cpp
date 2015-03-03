#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

void AddSum(int count[], double& Sum, double& MaxSum, double num[], int first, int last);

int main(){
        double *num;
        int size;
        double start, finish;
        int count[2] = {1, 999999999};
        ifstream file;
        file.open("testcase9.txt");                // txt파일 입력
        file >> size;                        // 입력할 숫자개수 입력

        num = new double[size];
        for(int i=0; i<size; i++)
                file >> num[i];                // 배열에 숫자 입력

        file.close();
        
        start = clock();                // 프로그램 시작시간 입력
        double MaxSum = -99999999;        // MaxSum 초기화
        
        double Sum = -99999999;        // Sum 초기화
        AddSum(count, Sum, MaxSum, num, 0, size-1); 
        finish = clock();  //프로그램 끝난시간 입력
        cout<<"연속하는 수의 갯수 : "<<count[1]<<endl;
        cout << "연속된 수의 최대합 : " << MaxSum << endl; //연속된 수의 최대합 출력
        printf("수행 시간  :  %lf" ,((finish - start)/CLOCKS_PER_SEC));// << " sec" << endl;;  //프로그램 수행시간 출력

        return 0;
}

void AddSum(int count[], double& Sum, double& MaxSum, double num[], int first, int last){
        if(first <= last){        // 입력받은 첫번재숫자부터 마지막숫자까지 if이하문 수행
                int mid = (first + last) / 2;        //mid는 입력받은 수의 개수의 중간값
                if(Sum>=0) {
                        Sum += num[first];
                        count[0]++;
                }        // Sum이 0보다 크거나같으면 Sum에 현재배열값 덧셈
                else { 
                        Sum = num[first];
                        count[0] = 1;
                }                // Sum이 0보다 작으면 현재배열값을 Sum에 입력 
                if(MaxSum<Sum) {
                        MaxSum = Sum;
                        count[1] = count[0];
                        //count[0] = 1;
                } 
                else if(MaxSum == Sum){
                        if(count[1] > count[0])
                                count[1] = count[0];
                        //count[0] = 1;
                }      // Sum이 MaxSum보다 크면 Sum의 값을 MaxSum에 입력
                AddSum(count, Sum, MaxSum, num, first+1, mid);
                AddSum(count, Sum, MaxSum, num, mid+1, last);        
        }
}