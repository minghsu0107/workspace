#include <stdio.h>
int arr[1000][1000];
int main() {
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            scanf("%d",&arr[i][j]);
        }
    }
    int max=0, len=0;
    for(int i=0;i<n;i++){
        if(arr[i][0]==1) len=1;
        for(int j=1;j<n;j++){
            if(arr[i][j]==1){
                
                if(arr[i][j]==arr[i][j-1]) len++;
                else len=1;
                max=len>max? len: max;
            }
        }
        len=0;
    }
    for(int j=0;j<n;j++){
        if(arr[0][j]==1) len=1;
        for(int i=1;i<n;i++){
           if(arr[i][j]==1){
                
                if(arr[i][j]==arr[i-1][j]) len++;
                else len=1;
                max=len>max? len: max;
           }
        }
        len=0;
    }
    for(int j=0;j<n-1;j++){
            if(arr[0][j]==1) len=1;
     
            int x=1,y=j+1;
            while(x<n && y<n){
                if(arr[x][y]==1){
                    
                    if(arr[x][y]==arr[x-1][y-1]) len++;
                    else len=1;
                    max=len>max? len:max;
                }
                x++;
                y++;
            }
            len=0;
    }
    for(int i=1;i<n-1;i++){
        if(arr[i][0]==1) len=1;
        int x=i+1,y=1;
        while(x<n && y<n){
                if(arr[x][y]==1){
                    
                    if(arr[x-1][y-1]==arr[x][y]) len++;
                    else len=1;
                    max=len>max? len:max;
                }
                x++;
                y++;
        }
        len=0;
    }
 
    printf("%d",max);
    return 0;
}