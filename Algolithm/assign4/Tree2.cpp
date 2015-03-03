#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int main(int argc, const char* argv[])
{
	int length, cut;
	int *num;//자르는 부분 + d0 + L 만큼 동적할당 
	int **sum;//동적계획법을 사용하기 위해 2차원 배열 동적 할당
	int result;
	ifstream file;
	double start, end;

	file.open(argv[1]);

	file>>length>>cut;

	num = new int[cut+2];

	num[0] = 0;
	for(int i = 1; i<=cut; i++)
		file>>num[i];
	num[cut+1] = length;

	sum = new int*[cut+1];//2차원 배열 동적할당 //자르는 부분 + d0
	for (int i = 0; i <= cut; ++i)
	{
		sum[i] = new int[cut+2];//자르는 부분 + d0 + L
	}

	for(int i=0; i<cut+1; i++)//d(i) + d(i+1) = 0
		for(int j=0; j<cut+2; j++)
			sum[i][j+1] = 0;
	start = clock();

	//code
	for(int k=0; k<cut; k++)//자르는 개수에 반비례하여 방법이 존재함
	{
		int i =0;
		int j = k+2;//처음에는 세 위치에서 하나를 자르기 때문에 di에서 i값의 차이가 2부터 시작됨
		for(int l = k; l <cut; l++)
		{
			int t_sum;
			bool first = true;//처음인 경우 최소값을 비교없이 저장//최소값 초기화!
			for(int m = i+1; m < j; m++)//임의의 두 위치 사이에서 자를 위치의 모든 경우를 구함
			{
				if(first)//처음인 경우
				{
					t_sum = sum[i][m] + sum[m][j];
					first = false;
				}
				else//두 번째 부터는 비교 시작
				{
					if(t_sum > (sum[i][m] + sum[m][j]))
						t_sum = sum[i][m] + sum[m][j];
				}
			}
			sum[i][j] = t_sum + num[j] - num[i];
			i++;
			j++;//2차원 배열의 대각선으로 이동
		}
	}

	end = clock();

	cout<<sum[0][cut+1]<<endl;//모든 경우의 최솟값 출력
	printf("%f\n\n", (end - start)/CLOCKS_PER_SEC);

	return 0;
}