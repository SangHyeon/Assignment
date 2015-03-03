#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

//분할 정복에 사용할 함수 선언
void FindMax(int count[], double& sum, double& max_sum, double num[], int first, int last);

int main(int argc, const char* argv[])
{
	double *num;
	int size;
	double max = -99999999;
	double sum = -99999999;
	double start, finish;
	int count[2] = {1, 999999999};//[0]은 최종 count, [1]은 임시 count
	ifstream file;
	file.open(argv[1]);//전달인자로 파일 이름 입력//  ./assign2 testcase10.txt
	file >> size;//배열의 크기 입력

	num = new double[size];
	for(int i=0; i<size; i++)
		file >> num[i];//숫자 입력

	start = clock();//수행시간 측정 시작
	
	FindMax(count, sum, max, num, 0, size-1);

	finish = clock();//수행시간 측정 끝
	cout<<"갯수 : "<<count[1]<<endl;
	cout << "최대값 : "<<max<< endl; //연속된 수의 최대합 출력
	printf("수행 시간  :  %lf\n \n", ((finish - start)/CLOCKS_PER_SEC));//프로그램 수행시간 출력

	file.close();

	return 0;
}

//함수 정의 부분
void FindMax(int count[], double& sum, double& max_sum, double num[], int first, int last)
{
	if(first <= last)
	{
		int mid = (first + last) / 2;
		if(sum>=0) //앞의 sum값이 0보다 크면 더해나감 // 음수의 경우는?
		{
			sum += num[first];
			count[0]++;
			//cout<<sum<<endl;//3번 알고리즘의 sum배열과 똑같이 출력됨
		}
		else //0보다 작은 값을 더하면 
		{
			if(sum<num[first]) //값이 계속해서 음수인 경우 값을 비교후 저장
				sum = num[first];
			count[0] = 1;
		}
		
		if(max_sum<sum) //최댓값을 비교
		{
			max_sum = sum;
			count[1] = count[0];
			//count[0] = 1;
		} 
		else if(max_sum == sum) //최댓값이 같은 경우 길이가 짧은 것을 저장
		{
			if(count[1] > count[0])
				count[1] = count[0];
			//count[0] = 1;
		}
		FindMax(count, sum, max_sum, num, first+1, mid);//왼쪽 먼저 오른쪽으로 순차적으로 해결//분할 정복....?
		FindMax(count, sum, max_sum, num, mid+1, last);//왼쪽이 끝나면 같은 방법으로 순차적으로 오른쪽으로 해결
	}
}