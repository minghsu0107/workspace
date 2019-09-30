#include <iostream>
#include <cstring>
using namespace std;

int v[101],w[101],k[1001];
int p[101][1001];  // 記錄放還是不放，false為不放，true為放
int output[101];
int len;
void pr(int x, int y) {
  for (int i=0; i<=x; i++) {
    for (int j=0; j<=y;j++){
      cout << p[i][j] << ",";
    }
    cout<<endl;
  }
}
void bag(int n,int ks){
    memset(k,0, sizeof(k));   
    for(int i=0;i<n;i++){  
      for(int j=ks;j>=w[i];j--){
        if (k[j-w[i]]+v[i]<k[j]){
          p[i][j] = 0;  
        }
        else if (k[j-w[i]]+v[i]>k[j]){   
          k[j] = k[j-w[i]]+v[i]; 
          p[i][j] = 1; 
        }
        else{
          p[i][j] = 2;  
        }
      }      
    }   
    cout << k[ks] << endl;  
}

void path(int n,int ks, int q){
    if(n<0){
       for (int i=0; i<=q; ++i){
         cout << output[i]<<" ";
         //output[i]=-1;
       }
       return; 
    }
    if(p[n][ks]==0){
       path(n-1,ks,q); 
    }
    else if(p[n][ks]==1){
       output[q] = n;
       path(n-1,ks-k[n],q+1); 
    }
    else if(p[n][ks]==2){
       
       output[q] = n;
       path(n-1,ks-k[n],q+1);
       //path(n-1,ks,q);
        
    }
}
void path2(int n,int ks){
    if(n<0){
       for (int i=0; i<len; ++i){
         cout << output[i]<<" ";
       }
       len=0;
       return; 
    }
    if(p[n][ks]==0){
       path2(n-1,ks); 
    }
    else if(p[n][ks]==1){
       output[len] = n;
       len++;
       path2(n-1,ks-k[n]); 
    }
    else if(p[n][ks]==2){
       path2(n-1,ks);
       output[len] = n;
       len++;
       //path2(n-1,ks-k[n]);
    }
}
int main(){ 
  int ks,n;
  while(cin>>n>>ks){  
    for(int i=0;i<n;i++){  
      cin>>w[i]>>v[i];  
    }  
    bag(n,ks);
    pr(n-1,ks);
    path(n-1,ks,0);
    //len=0;
    //path2(n-1,ks);
  }
}  