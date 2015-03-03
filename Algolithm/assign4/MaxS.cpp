#include <iostream>
#include <fstream>
using namespace std;

int main (int argc, char *argv[])
{
  fstream IN;
  IN.open(argv[1]);
  int m;
  int n;
  IN>>m>>n;
  int temp[n];
  int sum[n];
  int maxsum=0;
  int casesum= 0;
  
  int ** arr = new int* [m];
  for(int i=0; i<m ; i++){
    arr[i]= new int [n];
  }
  for(int i=0 ; i<m; i++){
    for(int j=0 ; j<n; j++){
      IN>>arr[i][j];
    }
  }
  
  int first=0;
  int last=0;
  while(1){  
    if(last==m){
      first++;
      last=first;
    }
    if(first==m)
      break;
    for(int j=0; j<n; j++){
      temp[j]=0;
      for(int i=first; i<last+1; i++){
        temp[j]+=arr[i][j];
     }
    }
    sum[0]=temp[0];
    maxsum=sum[0];
    for(int i=1; i<n; i++){
      if(sum[i-1]+temp[i]>0&&sum[i-1]>0)
        sum[i]=sum[i-1]+temp[i];
      else
        sum[i]=temp[i];
      if(sum[i]>maxsum)
        maxsum=sum[i];
    }
   // cout<<maxsum<<endl;
    if(casesum<maxsum)
      casesum=maxsum;

    last++; 
  }

  cout<<casesum<<endl;
  cout<<endl;

  return 0;
}