#include<stdio.h>
int main()
{
    char str[15];
    while(scanf("%s",str)!=EOF){
    int w,h;
    scanf("%d%d",&w,&h);
    int cnt;
    for(int i=0;str[i]!='\0';i++)
        cnt=i;
    cnt++;
    //printf("%d\n",cnt);
    char num[cnt][h][w];
    for(int i=0;i<cnt;i++)
        for(int j=0;j<h;j++)
            for(int k=0;k<w;k++)
                num[i][j][k]=' ';
    for(int i=0;i<cnt;i++)
        for(int j=0;j<h;j++)
            for(int k=0;k<w;k++)
            {
                if(str[i]=='0'){
                    if(j==0||j==h-1)
                    {
                        if(k>0&&k<w-2)
                            num[i][j][k]=str[i];
                    }
                    else if(j!=(h-1)/2) {
                        if(k==0||k==w-2)
                            num[i][j][k]=str[i];
                    }
                }
                if(str[i]=='1'){
                    if(j==0||j==h-1||j==(h-1)/2){
                        continue;
                    }
                    else {
                        if(k==w-2) num[i][j][k]=str[i];
                    }
                }
                if(str[i]=='2'){
                    //printf("here");
                    if(j==0||j==h-1||j==(h-1)/2)
                    {
                        if(k>0&&k<w-2) num[i][j][k]=str[i];
                    }
                    else if(j<(h-1)/2){
                        if(k==w-2) num[i][j][k]=str[i];
                    }
                    else {
                        if(k==0) num[i][j][k]=str[i];
                    }
                }
                if(str[i]=='3'){
                    if(j==0||j==h-1||j==(h-1)/2)
                    {
                        if(k>0&&k<w-2) num[i][j][k]=str[i];
                    }
                    else {
                        if(k==w-2) num[i][j][k]=str[i];
                    }
                }
                if(str[i]=='4'){
                    if(j==0||j==h-1) continue;
                    if(j>0&&j<(h-1)/2) {
                        if(k==0||k==w-2) num[i][j][k]=str[i];
                    }
                    if(j==(h-1)/2) {
                        if(k>0&&k<w-2) num[i][j][k]=str[i];
                    }
                    else if(k==w-2) num[i][j][k]=str[i];
                }
                if(str[i]=='5')
                {
                    if(j==0||j==(h-1)/2||j==h-1){
                        if(k>0&&k<w-2) {
                            num[i][j][k]=str[i];
                            //("%d",k);
                        }
                    }
                    if(j>0&&j<(h-1)/2) {
                        if(k==0) num[i][j][k]=str[i];
                    }
                    else if(j>(h-1)/2&&j<h-1){
                        if(k==w-2) num[i][j][k]=str[i];
                    }
                }
                if(str[i]=='6'){
                    if(j==0||j==(h-1)/2||j==h-1){
                        if(k>0&&k<w-2) num[i][j][k]=str[i];
                    }
                    if(j>0&&j<(h-1)/2) {
                        if(k==0) num[i][j][k]=str[i];
                    }
                    if(j>(h-1)/2&&j<h-1){
                        if(k==0||k==w-2) num[i][j][k]=str[i];
                    }
                }
                if(str[i]=='7'){
                    if(j==0) {
                        if(k>0&&k<w-2) num[i][j][k]=str[i];
                    }
                    if(j>0&&j<(h-1)/2) {
                        if(k==0||k==w-2) num[i][j][k]=str[i];
                    }
                    if(j>(h-1)/2&&j<h-1){
                        if(k==w-2) num[i][j][k]=str[i];
                    }
                }
                if(str[i]=='8'){
                    if(j==0||j==(h-1)/2||j==h-1) {
                        if(k>0&&k<w-2) num[i][j][k]=str[i];
                    }
                    else if(k==0||k==w-2) num[i][j][k]=str[i];
                }
                if(str[i]=='9'){
                    if(j==0||j==(h-1)/2){
                        if(k>0&&k<w-2) num[i][j][k]=str[i];
                    }
                    if(j>0&&j<(h-1)/2){
                        if(k==0||k==w-2) num[i][j][k]=str[i];
                    }
                    if(j>(h-1)/2&&j<h-1){
                        if(k==w-2) num[i][j][k]=str[i];
                    }
                }
            }
   for(int j=0;j<h;j++){
        for(int i=0;i<cnt;i++)
            for(int k=0;k<w;k++)
                printf("%c",num[i][j][k]);
        printf("\n");
    }
    }
   // printf("%c",num[0][0][0]);
}
