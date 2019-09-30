#include <iostream>
using namespace std;

void factor(int n){
   int i=2;
   while (i*i<=n){
       int pow=0;
       while(n%i==0){
           n/=i;
           pow+=1;
           if(n%i!=0){
               cout<<i<<"^"<<pow;
               if(n!=1){
                   cout<<"*";
               }
           }
       }
       i++;
   }
   if(n>1){
       cout<<n<<"^1"<<endl;
   }
}

int main(){
    int N;
    cin>>N;
    factor(N);
}