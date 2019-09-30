#include<cstdio>    
#include<queue>    
using namespace std;    
priority_queue<int,vector<int>,greater<int> > pq;    
int main(){    
    int n,num,cost;    
    while((scanf("%d",&n)==1)&&n){    //當讀入一個整數n 且n不為0 進入迴圈
        cost=0;    
        while(!pq.empty()) pq.pop();    
        for(int i=0;i<n;i++) {    
            scanf("%d",&num);    
            pq.push(num);    
        }    
        while(1){    
            int a,b,c;    
            a=pq.top();    
            pq.pop();    
            b=pq.top();    
            pq.pop();    
            c=a+b;    
            cost=cost+c;    
            if (pq.empty()) break;    
            pq.push(c);         
        }    
        printf("%d\n",cost);    
    }    
}    
