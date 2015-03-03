#include<iostream>
//#include"stdafx.h" //pre-compile?
#include<queue>
#include<fstream>
using namespace std;

//enum colorType = {white, gray, black};
int temp = 0;

struct NodeType
{//인접리스트 노드!
	int vertax;
	NodeType* link;
};

int MAX(int *com, int length)
{//최대값을 구하는 함수
	int temp = com[1];
	for(int i = 2; i<=length; i++)
		if(temp<com[i])
			temp = com[i];
	return temp;
}

int MIN(int *com, int length)
{//최소값을 구하는 함수
	int temp = com[1];
	for(int i = 2; i <= length; i++)
		if(temp>com[i])
			temp = com[i];
	return temp;
}

void dfs(bool **adjMatrix, int n, int v, bool *visited)
{//깊이우선탐색//인접행렬
	visited[v] = true;
	temp++;//노드 수!
//	cout<<v<<" ";

	for(int w = 1; w <= n; w++)
	{
		if(adjMatrix[v][w] && !visited[w])
		{//인접해 있는 노드들에 대해 다시 깊이우선 탐
			dfs(adjMatrix, n, w, visited);
		}
	}
}


void bfs(bool **adjMatrix, int n, int s, bool visited[], int d[])
{//너비우선탐색//인접행렬
	queue<int> Q;

	for(int v = 1; v <= n; v++)
	{
		visited[v] = false;
		d[v] = 0;
	}
	visited[s] = true;

	Q.push(s);//수정해야 할지도 모름
	d[s] = 0;//거리를 알기 위해//s에서 부터 얼마나 떨어져 있나
//	cout<<s<<" ";//방문된 원소 출력
	while(!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		for(int w = 1; w <= n; w++)
		{//인접한 행 전부 방문
			if(adjMatrix[v][w] && !visited[w])
			{//w~n까지 방문
				visited[w] = true;//방문 됐음을 표시
				d[w] = d[v] + 1;//거리 증가
//				cout<<w<<" ";
				Q.push(w);//큐에 추가
			}
		}
	}
}

void bfs(NodeType **adjList, int n, int s, bool visited[], int d[])
{//인접리스트//너비우선 탐색
	//인접행렬과 같은 방법으로 구현
	queue<int> Q;

	for(int v = 1; v <= n; v++)
	{
		visited[v] = false;
		d[v] = 0;
	}

	visited[s] = true;

	Q.push(s);
	d[s] = 0;
//	cout<<s<<" ";

	while(!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		NodeType *ptr = adjList[v];
		while(ptr)
		{
			if(ptr && !visited[ptr->vertax])
			{
				visited[ptr->vertax] = true;
				d[ptr->vertax] = d[v] + 1;
//				cout<<ptr->vertax<<" ";
				Q.push(ptr->vertax);
			}
			ptr = ptr->link;
		}
	}
}

int main(int argc, const char* argv[])
{
	bool **adjMatrix;
	NodeType **adjList;
	int n, m, k;
	int *count;//problem 1
	double prog_1=0;//result1
	ifstream IN;
	IN.open(argv[1]);

	IN>>n>>m;
	int i, j;

	count = new int[n+1];
	for(i = 1; i<=n; i++)
		count[i] = 0;//count를 0으로 초기화

	bool *visited;

	adjMatrix = new bool*[n+1];
	adjList = new NodeType*[n+1];

	for(i = 1; i <= n; i++)
		adjMatrix[i] = new bool[n+1];

	visited = new bool[n+1];

	for(int i =1; i<=n; i++){
		visited[i] = false;
		adjList[i] = NULL;
		for(int j =1; j<=n; j++)
			adjMatrix[i][j] = false;
	}
	
	for(i = 1; i <= m; i++)//그래프 작성
	{
		int u, v;
		NodeType *ptr1, *ptr2;
		IN>>u>>v;
		ptr1 = new NodeType;
		ptr2 = new NodeType;
		ptr1->vertax = v;
		ptr1->link=adjList[u];
//		adjList[u]=ptr1;
		ptr2->vertax = u;
		ptr2->link=adjList[v];
//		adjList[v]=ptr2;
		adjMatrix[u][v] = true;
		adjMatrix[v][u] = true;
	}
	IN>>k;
////////////PROG_1/////////////////////////////

	int compNum = 0;
	for(i = 1; i<=n; i++)
		if(!visited[i])
		{
			compNum++;//집단 수!
			dfs(adjMatrix, n, i, visited);
			count[compNum] = temp;//집단 내의 노드 수
			temp = 0;
		}

	for(i = 1; i<=compNum; i++)
		prog_1 += count[i];//집단의 크기 구함
	cout<<"PROG_1 : "<<compNum<<"  "<<MAX(count, compNum)<<"  "<<MIN(count, compNum)<<"  ";

	prog_1 /= compNum;//평균 구함

	cout<<prog_1<<endl;

///////////PROG_2//////////////////////////////////

	int *d;
	d = new int [n+1];

	for(i = 1; i<=n; i++)
	{//인접행렬 너비우선
		visited[i] = false;
		d[i] = 0;
	}
	//bfs(adjMatrix, n, 1, visited, d);//너비우선

	bool * f_visited = new bool[n+1];//final visited
	//집단 내에서 해당 노드를 기준으로 다른 노드들의 거리를 구하였는지 판단하는 배열
	for(i = 1; i <= n; i++)
		f_visited[i] = false;//false로 초기화

	int bigger = 0;//제일 큰 집단의 노드 수
	double prog_2 = 0;//prog_2의 답

	for(i = 1; i < n; i++)
	{
		bool judge = false;//집단인가?
		int temp=0;
		int cnt = 0;//친구관계의 수
		bfs(adjList, n, i, visited, d);
		for(int k = i+1; k <= n; k++)
		{
			temp += d[k];//거리
			if(d[k] > 0)//친구관계인 경우
				cnt++;//노드 수 추가
		}
		for(j = i+1; j <= n; j++)
		{
			if(!f_visited[j] && visited[j])
			{//bfs로 방문했지만 거리를 아직 안구한 경우
				judge = true;//한 집단임!
				f_visited[j] = true;
				//집단 내에서 해당 노드를 기준으로 다른 노드들의 거리를 구함
				bfs(adjList, n, j, visited, d);
				for(int k = j; k <= n; k++)
				{
					temp += d[k];//거리 추가
					if(d[k] > 0)
						cnt++;//노드 수 추가
				}
			}	
		}
		if(judge)//집단일 때
		{
			if(bigger <= cnt)
			{//집단의 노드수 비교
				if(bigger == cnt)
				{	//노드의 수가 같은 경우 더 작은 값을 저장
					if((double)temp/cnt < prog_2)
						prog_2 = (double)temp/cnt;
				}
				else//노드의 수가 더 크면 바로 저장
					prog_2 = (double)temp/cnt;
				bigger = cnt;//더 큰 수로 초기화
			}
		}
	}
	cout<<"PROG_2 : "<<prog_2<<endl;
//	cout<<endl;

/////////////PROG_3/////////////////////////

	int *cnt_prog_3 = new int[n+1];//조건을 충족시키는 정점
	for(i = 1; i <= n; i++)
		cnt_prog_3[i] = 1;//일단 1로 초기화
	for(i = 0; i <k; i++)
	{//친구가 아예 없는 경우도 계산!
		for(j = 1; j <= n; j++)
		{//하나의 행씩 비교
			int cnt = 0;//친구의 수
			for(int l = 1; l <= n; l++)
			{
				if(adjMatrix[j][l])
					cnt++;//친구수 증가
			}
			if(cnt<=i)//조건에 안맞으면
			{
				cnt_prog_3[j] = 0;
				for(int l = 1; l <= n; l++)//차례대로 친구 삭제
				{
					if(adjMatrix[j][l])
					{//무향그래프이므로 반대의 경우도 같이 삭제
						adjMatrix[j][l] = false;
						adjMatrix[l][j] = false;
					}
				}
			}
		}
	}

	int prog_3 = 0;
	for(i = 1; i <= n; i++)
		prog_3 += cnt_prog_3[i];//조건에 충족하는 노드 수

	cout<<"PROG_3 : "<<prog_3<<endl;

	cout<<endl;

	return 0;
}
