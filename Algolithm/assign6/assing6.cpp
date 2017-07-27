#include <iostream>
#include <string.h>
#include <fstream>
#include <stack>

using namespace std;

//test

int find_string(string s, string ver[], int length);//return index of string
void t_dijkstra(int start, int **adjMatrix, int d[], bool s[], int path[]);//dijkstra algorithm

int router, link;//정점, 에지 수

int main(int argc, char const *argv[])
{
	
	int *d, *path, *next;//거리, 경로
	bool *s;//확정 집단
	int **adjMatrix;//인접행렬
	string *vertex;//정점들의 이름
	string s_start;//시작 정점의 이름
	int ver_count = 0;
	int s_count, start;//시작 정점 수, 시작 정점

	fstream File;
	File.open(argv[1]);

	File>>router>>link;

	d = new int[router];//거리

	next = new int[router];//정점으로 전달하기 위해 거치는 정

	s = new bool[router];//확정 정점들의 집단

	path = new int[router];

	vertex = new string[router];
	//2차원 배열 생성
	adjMatrix = new int*[router];

	for (int i = 0; i < router; ++i)
		adjMatrix[i] = new int[router];

	for (int i = 0; i < router; ++i)
		for (int j = 0; j < router; ++j)
		{
			if(i == j)
				adjMatrix[i][j] = 0;//자신의 경로
			else
				adjMatrix[i][j] = 99999999;//최댓값(무한대)로 초기화
		}

	for (int i = 0; i < link; ++i)
	{
		string temp1, temp2;//임시 vertex
		int index1, index2;//임시 index
		int cost;
		File>>temp1>>temp2>>cost;
		index1 = find_string(temp1, vertex, router);
		index2 = find_string(temp2, vertex, router);
		if(index1 == -1)//vertex가 처음 입력된 경우 배열에 저장 후 index저장
		{
			vertex[ver_count] = temp1;
			index1 = ver_count;
			ver_count++;//vertex 배열의 index
		}

		if(index2 == -1)//index1과 같음
		{
			vertex[ver_count] = temp2;
			index2 = ver_count;
			ver_count++;
		}

		adjMatrix[index1][index2] = cost;//비용 입력
		adjMatrix[index2][index1] = cost;
	}

	File>>s_count;

	for (int i = 0; i < s_count; ++i)
	{
		File>>s_start;
		start = find_string(s_start, vertex, router);
		cout<<"start    :   "<<start<<endl;
		t_dijkstra(start, adjMatrix, d, s, path);

		for (int j = 0; j < router; ++j)
		{
			if(j == start)
			{
				cout<<vertex[j]<<"	"<<"-  "<<"	"<<d[j]<<endl;
				continue;
			}
			else if(d[j] == 99999999)
			{
				cout<<vertex[j]<<"	"<<"-  "<<"	"<<d[j]<<endl;
				continue;
			}

			stack<int> s;//역추적하기 위한 스택

			for (int k = j; k != start; k = path[k])
				s.push(k);

			cout<<vertex[j]<<"	"<<vertex[s.top()]<<"	"<<d[j]<<endl;
		}
		cout<<endl;
	}



	File.close();
	
	return 0;
}

int find_string(string s, string ver[], int length)
{
	for (int i = 0; i < length; ++i)
		if(ver[i] == s)
			return i;
	return -1;
}

void t_dijkstra(int start, int **adjMatrix, int d[], bool s[], int path[])
{
	for (int i = 0; i < router; ++i)
	{
		s[i] = false;//확정되지 않은 정점은 false로 초기화
		d[i] = adjMatrix[start][i];//시작정점을 기준으로 거리 초기화
		path[i] = start; //처음은 다 시작정점의 값을 가짐 cuz 경로
	}

	s[start] = true;//시작 정점은 방문!
	d[start] = 0;//자신까지의 거리는 0

	for (int i = 0; i < router-1; ++i)
	{
		int min = 99999999;
		int m_index = 0;

		for (int j = 0; j < router; ++j)
		{
			if(!s[j])//확정되지않은 집단 중에서
			{
				if(min > d[j])//최솟값을 찾음
				{
					min = d[j];
					m_index = j;
				}
			}
		}

		s[m_index] = true; //제일 작은 값을 확정 집단에 추가

		for (int j = 0; j < router; ++j)
		{
			if(!s[j])//확정되지않은 정점들 중
			{
				if(d[m_index] + adjMatrix[m_index][j] < d[j])//거쳐가는 게 더 적은 비용일 때
				{
					d[j] = d[m_index] + adjMatrix[m_index][j];//최솟값 저장
					path[j] = m_index;//역추적...
				}
			}
		}
	}
}
