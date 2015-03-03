#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;

void Insertion(double num[], int i);

int main(int argc, const char* argv[]) 
{
	double *num;//배열 동적할당
	int size;//배열의 크기
	int fre;//최빈값
	int count;//빈도 수
	fstream file;
	double start, end;

	file.open(argv[1]);//파일 이름을 전달인자로 전달
	file>>size;

	num = new double[size];
	for(int i=0; i<size; i++)
		file>>num[i];

	start = clock();

	//코드 작성
	for(int index = 0; index < size; index++)
		Insertion(num, index);//처음부터 끝까지 검색하며 정렬

	//최빈값 구하기
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

void Insertion(double num[], int i)
{
	double temp = num[i];//임시로 값을 저장
	int k;//알맞는 위치를 찾기 위한 변수
	for (k = i-1; k >= 0; k--)
	{
		if(num[k]>temp)//임시로 저장한 값보다 더 큰 경우 한 칸씩 뒤로
			num[k+1] = num[k];
		else//더 큰값이 없는 경우 
			break;
	}
	num[k+1] = temp;//임시값보다 작은 값 다음 index에 저장
}