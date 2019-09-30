#include<stdio.h>
int main(){
    char name[200];
    int num[65536] = {0};
    FILE *fp1;
    scanf("%s", name);
    fp1 = fopen(name, "rb");
    int n;
    short int maxnum, maxtimes, now;
    fread(&n, sizeof(int), 1, fp1);
    fread(&maxnum, sizeof(short int), 1, fp1);
    num[maxnum + 32768] ++;
    maxtimes = 1;
    for(int i = 0; i < n - 1; i++){
        fread(&now, sizeof(short int), 1, fp1);
        num[now + 32768] ++;
        if(num[now + 32768] > maxtimes ||
           (num[now + 32768] == maxtimes && now > maxnum)){
            maxnum = now;
            maxtimes = num[now + 32768];
        }
    }
    printf("%hd\n%hd", maxnum, maxtimes);
    fclose(fp1);
    return 0;
}