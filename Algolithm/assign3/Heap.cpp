#include<iostream>
#include<fstream>
#include<time.h>

using namespace std;

void rebuildHeap(double num[], int root, int length);
void Heapsort(double num[], int length);

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
	Heapsort(num, size);

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
	
/*	for (int i = 0; i < size; i++)
		cout<<num[i]<<" ";
	cout<<endl;
*/
	cout<<fre<<"  "<<count<<"   수행 시간 : ";
	printf("%f\n\n", (end - start)/CLOCKS_PER_SEC);

	return 0;
}

void rebuildHeap(double num[], int root, int length)
{//제일 큰 값이 root가 되도록!
	int current = root;//현재 위치 설정
	//int largerChild;
	int t_root = num[root];//임시 root값//부모 노드

	while(2*current + 1 < length)//자식의 위치가 배열의 길이를 넘어서지 않을 때까지
	{
		int leftChild = 2*current + 1;//왼쪽 자식의 위치
		int rightChild = leftChild + 1;//오른쪽 자식의 위치
		int largerChild;//더 큰 값

		if((rightChild < length) && (num[rightChild] > num[leftChild]))
			largerChild = rightChild;//자식이 배열 내에 있고 오른쪽 자식이 더 큰 경우
		else
			largerChild = leftChild;//왼쪽 자식이 더 큰 경우

		if(t_root < num[largerChild])//부모노드가 자식노드보다 작은 경우
		{
			num[current] = num[largerChild];
			current = largerChild;//현재 위치를 재설정
		}
		else
			break;//rebuild 완료!
	}
	num[current] = t_root;//현재 위치의 값에 임시 root값 저장//매우 중요
}

void Heapsort(double num[], int length)
{
	for(int root = length/2 -1; root >= 0; root--)//저장된 값들을 전달 받은 길이 만큼 rebuild함
		rebuildHeap(num, root, length);

	int heap_size = length;

	for(int last = length -1; last > 0; last--)
	{
		//제일 큰 값을 맨 뒤로 보냄
		double temp = num[0];
		num[0] = num[last];
		num[last] = temp;

		heap_size--;//길이를 줄임//last에 값은 sort된 상태!

		rebuildHeap(num, 0, heap_size);//root노드의 위치를 찾아줌
	}
}