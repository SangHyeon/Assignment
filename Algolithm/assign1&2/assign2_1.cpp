#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

//Divide And Conquer
void D_C(double num[], double sum[], int first, int last);

int main(int argc, char const *argv[])
{
	double *num;//입력값 저장 배열
	int size, index, count = 1;//배열의 크기, 최댓값 index, 길이
	double max;//최종 최댓값
	double *sum;//num배열의 각 index에서의 최대값을 저장//과제 1-3과 같은 역할
	double start, finish;//시간측정을 위한 변수
	ifstream file;
	
	file.open(argv[1]);//command line에서전달인자로 파일 이름 입력//  ./assign2 testcase10.txt
	file >> size;//배열의 크기 입력
	
	num = new double[size];
	for(int i=0; i<size; i++)
		file >> num[i];//숫자 입력
	
	sum = new double[size];
	
	start = clock();//수행시간 측정 시작
	
	D_C(num, sum, 0, size-1);
	
	max = sum[0];//최댓값을 num배열의 처음 값으로 초기화
	for(int i=1; i<size; i++)//최댓값을 찾음
	{
		if(max<sum[i])//최댓값인 경우
		{
			count =1;//길이를 세기 시작
			max = sum[i];//최댓값으로 저장
			index = i-1;//0이하의 값이 나올때까지 검색//이유는 재귀함수에서..
			while(1)
			{
				if(sum[index]>0)
					count++;
				else
					break;//0이하의 값이 나온 경우 loop탈출
				index--;
			}
		}
		else if(max == sum[i])//최댓값이 같은 경우
		{
			int temp_count = 1;//최댓값인 경우와 같은 방법으로 길이 찾음
			index = i-1;
			while(1)
			{
				if(sum[index]>0)
					temp_count++;
				else
					break;
				index--;
			}
			if(temp_count < count)//길이 비교 후 짧은 것으로 저장
				count = temp_count;
		}
	}
	
	
	
	finish = clock();//수행시간 측정 끝
	cout<<"길이 : "<<count<<"	";
	cout << "최대값 : "<<max<< endl; //연속된 수의 최대합 출력
	printf("수행 시간  :  %lf \n \n" ,((finish - start)/CLOCKS_PER_SEC));//프로그램 수행시간 출력
	
	file.close();
	delete []num;//메모리 해제
	delete []sum;
	
	return 0;
}

void D_C(double num[], double sum[], int first, int last)
{
	if(first == last)
	{
		sum[first] = num[first];
		return;
	}
	int mid = (first+last)/2;

	D_C(num, sum, first, mid);//왼쪽 먼저
	/*for(int i=0; i<size; i++)  sum이 어떻게 저장되어 가는지 확인
	 cout<<sum[i]<<" ";
	 cout<<endl;
	 cout<<"큰 왼쪽 끝"<<endl;*/
	D_C(num, sum, mid+1, last);//왼쪽에서 오른쪽 방향으로
	
	//합치기!
	if(sum[mid]<=0)//중간값(왼쪽의 맨끝)이 0이하일 경우 더하지 않음(최댓값 검색 시작점)
		return;
	else// if((sum[mid]+sum[mid+1]) > 0) //더해서 양수인 경우 더함
	{
		sum[mid+1]+=sum[mid];//중간값을 중간값 다음 값에 저장
		for(int i=mid+2; i<=last; i++){ //저장한 값을 새로이 저장
			if(!((sum[i] = sum[i-1]+num[i])<0))//새로이 더해가는 값들 전까지만 더함
				sum[i] = sum[i-1]+num[i];//원래의 sum값에 더함
			else
				break;
		}
	}
	/*for(int i=0; i<size; i++) //마찬가지로 sum 배열 확인
	 cout<<sum[i]<<" ";
	 cout<<endl;*/
}
