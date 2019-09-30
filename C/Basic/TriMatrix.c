#include <stdio.h>
double A[17][17];
double X[17];
double Y[17];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            scanf("%lf",&A[i][j]);
        }
    }
    for(int i=1;i<=n;i++){
        scanf("%lf",&Y[i]);
    }
    double sum;
    for(int i=n;i>=1;i--){
        sum=0;
        for(int j=n;j>i;j--){
           sum+=A[i][j]*X[j]; 
        }
        X[i]=(Y[i]-sum)/A[i][i];
    }
    for(int i=1;i<=n;i++){
        printf("%f\n",X[i]);
    }
    return 0;
}