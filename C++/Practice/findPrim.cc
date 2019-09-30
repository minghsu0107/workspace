#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

int composite[10000];

typedef int (*DIG)(int);
int digit(int);
void find(int,int);
void find2(int,int,int,DIG);


int main(){
    int n,c;
    cout<<"輸入n與行數: ";
    cin>>n>>c;
    find(n,c);
    cout<<endl;
    
    int x1,x2,col;
    cout<<"Range[x1,x2]:";
	cin>>x1>>x2;
	cout<<"column: ";
	cin>>col;
	find2(x1,x2,col,digit);
}
void find(int n,int column){ 
    int count=0; //紀錄目前質數個數
    for (int i=2;i<=n;i++){
      composite[i]=0;
  }
  int j=2;
  while(j*j<=n){
     while (composite[j]==1){
         j++;
     }
     for (int i=j*2;i<=n;i+=j){
         composite[i]=1; 
     }
     j++;
  }
  for (int i=2;i<=n;i++){
      if(composite[i]==0){
          if(count%column==column-1){ //一行有column個 
                                      //如果count除以8餘7 則表處於行末 需換行
              cout<<setw(5)<<i<<endl;
          }
          else{
              cout<<setw(5)<<i;
          }
          count++;
          
      }
  }
}
void find2(int x1,int x2,int col,DIG dig){
	//找質數
	int i,j;
	int count=0;
	for(i=x1 ;i<=x2  ;i++){   //需要測試哪些數字 上下界
		for(j=2; j<=i ;j++){  //要用什麼方式找到質數
			if(i%j==0 ) break;
		}
    		if(i==j){
    		    int d=dig(x2);
    		    if(count%col==col-1){
    		        cout<<setw(d)<<i<<endl;
    		    }
    		    else{
    		        cout<<setw(d)<<i;
    		    }
    		    count++;
    		}
	}
}
int digit(int n){
    int k=log10(n);//double log10(double x);
    return (k+1)+1;
}