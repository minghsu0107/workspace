#include <iostream>
#include <string>
using namespace std;

void pr(string arr[],int len){
    for (int i=0;i<len;i++){
      cout<<arr[i]<<endl;
    }
}

void swap(string &a,string &b) {
    string t = a; 
    a = b; 
    b = t;
}
void swap2(string* a,string* b) {
    string t = *a; 
    *a = *b; 
    *b = t;
}

void sort(string arr[],int len){
    int flag = 1; 
    for(int i = 0; i < len-1 && flag == 1; i++) { 
        flag = 0; 
        for(int j = 0; j < len-i-1; j++) { 
            if(arr[j+1].compare(arr[j])<0) {
                //swap(arr[j+1],arr[j]);
                swap2(&arr[j+1],&arr[j]);
                flag = 1; 
            } 
        } 
    }
    
}

int main(){
  int n;
  cin>>n;
  string arr[n];
  for(int i=0;i<n;i++){
    string s;
    cin>>s;
    arr[i]=s;
  }
  sort(arr,n);
  pr(arr,n);
}