#include <stdio.h>
#include <string.h> 
char _;
int arr[26] = {}, n, map[26][26] = {};
char Ans[100],s[100];
void Perm(int d, int N)  
{   
    if (d==N)  
    {   
        for (int i=0; i<N; i++)  
            printf("%c",Ans[i]);
        puts("");  
        return;  
    } 
    for (int i=0; i<26; i++)  
    {  
        if (arr[i]>0){    
          arr[i]--;        
          Ans[d] = i + 'a';
          int valid = 1;
          if (d >= 1) {
             if (map[Ans[d-1] - 'a'][Ans[d] - 'a']) valid = 0;
          }
          if (valid) Perm(d+1, N);  
          arr[i]++;       
        }
    }  
}  
int main()  
{  
    scanf("%s", s); 
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
       char rule[3];
       scanf("%s", rule); 
       map[rule[0] - 'a'][rule[1] - 'a'] = 1;
    }
    int len=strlen(s);
    for (int i = 0; i < len; i++) arr[s[i] - 'a']++;
    Perm(0,len);  
}