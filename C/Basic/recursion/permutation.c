#include <stdio.h>  
int Used[10];  // Ans用來存放一組可能的答案
int Ans[10],num[10];
void Perm(int d,int N)  
{  
    int i;  
    if (d==N)  
    {   
		int f = 0;
        for (i=0; i<N; i++) {
			if (f) printf(" ");
		    printf("%d", Ans[i]);  // 印出一組可能的答案
		    f = 1;
		}
        puts("");
        return;  
    }  
    for (i=0; i<N; i++)  
    {  
        if (Used[i]) continue;  
        Used[i]=1;  
        Ans[d]=num[i];  
        Perm(d+1,N);  
        Used[i]=0;  
    }  
} 
void sort(int arr[], int len){
	int flag = 1; 
    for(int i = 0; i < len-1 && flag == 1; i++) { 
        flag = 0; 
        for(int j = 0; j < len-i-1; j++) { 
            if(arr[j+1] < arr[j]) {
                int tmp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = tmp;
                flag = 1; 
            } 
        } 
    }
}
int main()  
{  
    int i, n;  
    scanf("%d",&n); 
    for (i=0; i<n; i++) 
		scanf("%d",&num[i]), Used[i]=0;  
	sort(num,n);
    Perm(0,n);  
}  
