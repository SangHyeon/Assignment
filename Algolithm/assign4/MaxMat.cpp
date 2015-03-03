#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int Max_Mat(int **mat, int m, int n);//2차원 최댓값
int Max_Mat2(int **mat, int m, int n);
int Max_Sum(int num[], int n);//1차원 최댓값

int main(int argc, const char* argv[])
{
	int m, n;//행, 열
	int** MAT;//double pointer //2차원 배열
	int result;
	ifstream file;
	double start, end;

	file.open(argv[1]);

	file>>m>>n;
	MAT = new int*[m];

	for(int i=0; i < m; i++)
		MAT[i] = new int[n]; // 2차원 배열 동적 할당 

	for (int i = 0; i < m; i++) {// 2차원 배열에 값 입력
		for(int j=0; j<n; j++){
			file>>MAT[i][j];
		}
	}


	start = clock();

	//code
	if(m>n)//O(m^2*n) 이므로 열 위주로 변경 
		result = Max_Mat2(MAT, m, n);
	else
		result = Max_Mat(MAT, m, n);

	end = clock();

	cout<<result<<endl;
	printf("%f\n\n", (end - start)/CLOCKS_PER_SEC);

	return 0;
}

int Max_Mat(int **mat, int m, int n)
{
	int max = mat[0][0];//최댓값을 맨 처음 값으로 초기화 
	int t_max;

	for(int i=0; i<m; i++)
	{
		int num[n];//행들의 열단위 합을 저장하기 위한 배열
		for(int i=0; i<n; i++)
			num[i]=0;//0으로 초기화
		for(int l = i; l<m; l++)
		{
			for(int k = 0; k<n; k++)
			{//num에 같은 열에 위치한 값들을 더함
				num[k] += mat[l][k];
			}
			
			t_max = Max_Sum(num, n);//최대 부분합 구함
		
			if(t_max>max)
				max = t_max;//더 큰 부분합 저장
		}
	}

	return max;
}

int Max_Mat2(int **mat, int m, int n)
{
	int max = mat[0][0];//최댓값을 맨 처음 값으로 초기화 
	int t_max;

	for(int i=0; i<n; i++)
	{
		int num[m];//행들의 열단위 합을 저장하기 위한 배열
		for(int i=0; i<m; i++)
			num[i]=0;//0으로 초기화
		for(int l = i; l<n; l++)
		{
			for(int k = 0; k<m; k++)
			{//num에 같은 열에 위치한 값들을 더함
				num[k] += mat[k][l];
			}
			
			t_max = Max_Sum(num, m);//최대 부분합 구함
		
			if(t_max>max)
				max = t_max;//더 큰 부분합 저장
		}
	}

	return max;
}

int Max_Sum(int num[], int n)
{
	int maxsum = num[0];
	int sum[n];//동적계획법을 사용하기 위해 선언
	sum[0] = num[0];

	for (int i = 1; i < n; i++)
	{//계속 더해나가면서 0이하로 값이 바뀌면 새로 시작
		if (sum[i-1] > 0)
		{
			sum[i] = sum[i-1] + num[i];
		}
		else
		{   
			sum[i] = num[i];
		}
	}

	for (int i = 1; i < n; i++)
	{//최댓값 탐색
		if (maxsum < sum[i])
		{
			maxsum = sum[i];
		}
	}

	return maxsum;
}