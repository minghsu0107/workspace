#include <iostream>    
#include <algorithm>    
    
using namespace std;    
    
int main(){    
  int N;      
  long long int babe[10100];    
  cin >> N;    
  for(int i=0;i<N;i++){    
    cin >> babe[i];    
  }    
  sort(babe,babe+N);  
  long long int fine=0;     
  for(int i=0;i<N;i++){    
    fine+=(N-1-i)*100*babe[i];    
  }    
  cout << fine;    
  return 0;    
}  