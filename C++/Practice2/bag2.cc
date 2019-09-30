#include <iostream>
#include <cstring>
using namespace std;

int v[101],w[101],k[1001];
bool p[101][1001];  // 記錄放還是不放，false為不放，true為放
int ks,n;   

int main(){  
  while(cin>>n>>ks){  
    for(int i=0;i<n;i++){  
      cin>>w[i]>>v[i];  
    }  
    memset(k,0, sizeof(k));   
    memset(p, false, sizeof(p));    // 初始化為false
    for(int i=0;i<n;i++){  
      for(int j=ks;j>=w[i];j--){  
        if (k[j-w[i]]+v[i]>k[j]){   
          k[j] = k[j-w[i]]+v[i]; 
          p[i][j] = true; // 有放
        }         
      }      
    }   
    cout << k[ks] << endl;  
    // 往回逆推，求出所有放入的物品。
    for (int i = n-1, j = ks; i >= 0; --i){
        if (p[i][j]){  // 背包有該物品
            cout << "背包裡面有第" << i << "個物品"<<endl;
            j -= w[i];
        }
    }
    cout<<endl;
  }
}  
/*
如果是要求恰好装满背包，那么在初始化时除了k[0]为0其它k[1..ks]均设为-∞，
这样就可以保证最终得到的k[ks]是一种恰好装满背包的最优解。
如果并没有要求必须把背包装满，而是只希望价格尽量大，初始化时应该将k[0..ks]全部设为0。
*/