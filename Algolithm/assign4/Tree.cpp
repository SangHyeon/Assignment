#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int Find_Min(int num[], int i, int j);

int main(int argc, const char* argv[])
{
	int length, cut;
	int *num;
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

	for(int i = 0; i<cut+2; i++)
		cout<<num[i]<<" ";
	cout<<endl<<endl;

	start = clock();

	//code
	result = Find_Min(num, 0, length);

	end = clock();

	cout<<result<<endl;
	printf("%f\n\n", (end - start)/CLOCKS_PER_SEC);

	return 0;
}

int Find_Min(int num[], int i, int j)
{
	if( (i == j+1 ) || (i >= j) )
		return 0;
	int min1, min2;
	int count = j-i-1;
	int *t_min1 = new int[count];
	int *t_min2 = new int[count];

	for(int k = 1; k <= count; k++)//C(i, k)
	{
		t_min1[k-1] = Find_Min(num, i, i+k);
		if(k == 1)
			min1 = t_min1[1];
		else
		{
			if(min1<t_min1[k-1])
				min1 = t_min1[k-1];
		}
		//cout<<t_min1[k-1]<<endl;
	}

	for(int k = 1; k <= count; k++)
	{
		t_min2[k-1] = Find_Min(num, i+k, j);
		if(k == 1)
			min2 = t_min2[1];
		else
		{
			if(min2<t_min2[k-1])
				min2 = t_min2[k-1];
		}

		//cout<<t_min2[k-1]<<endl;
	}

	return (num[j]-num[i] + min1 + min2);
}