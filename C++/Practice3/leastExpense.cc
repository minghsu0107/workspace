#include<iostream>  
#include <queue>
using namespace std;  

priority_queue<int, vector<int>, greater<int> > q;
int main(){  
    int n,num,cost;  
    cin>>n;
    cost=0;  
    while(!q.empty()) q.pop();  
    for(int i=0;i<n;i++) {  
        cin>>num;  
        q.push(num);  
    }  
    while(1){  
        int a,b,c;  
        a=q.top();  
        q.pop();  
        b=q.top();  
        q.pop();  
        c=a+b;  
        cost=cost+c;  
        if (q.empty()) break;  
        q.push(c);       
    }  
    cout<<cost<<endl;
}  