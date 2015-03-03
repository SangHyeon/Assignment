#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>

using namespace std;

void QuickSort1(double num[], int first, int last);

int main(int argc, const char* argv[]) 
{
	double *num;
	int size;
	int fre;//최빈값
	int count;//빈도수
	fstream file;
	double start, end;

	file.open(argv[1]);//파일 이름을 전달인자로 전달
	file>>size;

	num = new double[size];
	for(int i=0; i<size; i++)
		file>>num[i];

	start = clock();

	//코드 작성
	QuickSort1(num, 0, size-1);

	fre = num[0];//배열 처음 값으로 초기화
	count = 0;//빈도수 초기화
	int temp_fre = num[0];//임시 최빈값
	int temp_cnt=1;//임시 빈도수
	for (int i = 1; i < size; i++)
	{
		if(num[i]==temp_fre)
			temp_cnt++;//같은 숫자가 나오는 경우 임시 빈도수 증가
		else
		{
			if(temp_cnt>=count)
			{
				if(temp_cnt == 1)
					fre = num[i];//중복되는 숫자가 없는 경우 제일 큰 값 출력
				else
					fre = temp_fre;//최빈값
				count = temp_cnt;//최대 빈도수
			}
			temp_fre = num[i];//임시값 초기화
			temp_cnt = 1;//임시값 초기화
		}
	}
	if(temp_cnt > count)//제일 큰 값이 연속되는 경우
	{
		count = temp_cnt;
		fre = temp_fre;
	}
	end = clock();
	/*for (int i = 0; i < size; i++)
		cout<<num[i]<<" ";
	cout<<endl;*/

	cout<<fre<<"  "<<count<<"   수행 시간 : ";
	printf("%f\n\n", (end - start)/CLOCKS_PER_SEC);

	return 0;
}

void QuickSort1(double num[], int first, int last) //  병합정렬 2 
{
	if(first>=last)
		return;
	double temp;//swap할 때 사용
	int left = first+1;//맨 왼쪽
	int right = last;//맨 오른쪽
	srand(time(NULL));
	int pivot = rand()%(last-first) + first;//배열 범위 내에서 피벗을 랜덤으로 설정
	//if(pivot < first)
	//	pivot+=first;
	//피벗에 있는 값과 맨 처음 값을 서로 바꿈
	temp = num[pivot];//임시로 피벗 값을 저장
	num[pivot] = num[first];
	num[first] = temp;

	while(left <= right)
	{//양끝에서 서로 만날때까지 
		while((left <=last) && (num[left]<num[first]))
			left++;//왼쪽에 있는 값이 맨 처음 값(피벗 값)보다 클때 까지
		while((right >= first+1) && (num[right]>=num[first]))
			right--;//위와 반대의 경우
		if(left<=right)
		{
			//값을 서로 바꾼 뒤 위치를 증/감
			temp = num[left];
			num[left] = num[right];
			num[right] = temp;
			left++;
			right--;
		}
	}
	//피벗에 있는 값을 마지막 right에 있는 값과 바꿈//피벗 값을 원래 자리로 변경
	temp = num[first];
	num[first] = num[right];
	num[right] = temp;
	//반씩 나눠서 다시 정렬(피벗 값 제외)
	QuickSort1(num, first, right-1);
	QuickSort1(num, right+1, last);
}
