#include <stdio.h>
//注意邊界檢查，先檢查再移動，才不會造成 Runtime Error
//檢查有多少障礙物時不可以檢查整台坦克所在的區域 檢查新增的區域即可
int map[500][500];
int main(){
    int N, M, L, W, I, O;
    scanf("%d %d %d %d %d", &N, &M, &L, &W, &O);
    for(int i = 0; i < O; i++){
            int x, y;
            scanf("%d %d", &x, &y);
            map[y][x] = 2;
    }
    for(int i = 0; i < L; i++){
        for(int j = 0; j < W; j++){
            map[i][j] = 1;
        }
    }
    int x = 0, y = 0;
    while(scanf("%d", &I) != EOF){
        int cnt = 0;
        switch(I){
                case 0:
                    for(int i = 0; i < N; i++){
                        for(int j = 0; j < M; j++){
                            printf("%d", map[i][j]);
                        }
                        printf("\n");
                    }
                    break;
                case 1:
                    if(x+W < M){
                            for(int i = 0; i < L; i++)
                                if(map[y+i][x+W] == 2) cnt++;
                            if(cnt < 2){
                                for(int i = 0; i < L; i++){
                                    map[y+i][x+W] = 1, map[y+i][x] = 0;
                                }
                                x++;
                            }
                    }
                    break;
                case 2:
                    if(y+L < N){
                            for(int i = 0; i < W; i++)
                                if(map[y+L][x+i] == 2) cnt++;
                            if(cnt < 2){
                                for(int i = 0; i < W; i++){
                                    map[y+L][x+i] = 1, map[y][x+i] = 0;
                                }
                                y++;
                            }
                    }
                    break;
                case 3:
                    if(x-1 >= 0){
                            for(int i = 0; i < L; i++)
                                if(map[y+i][x-1] == 2) cnt++;
                            if(cnt < 2){
                                for(int i = 0; i < L; i++){
                                    map[y+i][x-1] = 1, map[y+i][x+W-1] = 0;
                                }
                                x--;
                            }
                    }
                    break;
                case 4:
                    if(y-1 >= 0){
                            for(int i = 0; i < W; i++)
                                if(map[y-1][x+i] == 2) cnt++;
                            if(cnt < 2){
                                for(int i = 0; i < W; i++){
                                    map[y-1][x+i] = 1, map[y+L-1][x+i] = 0;
                                }
                                y--;
                            }
                    }
                    break;
                case 5:
                    if(x+W < M && y+L < N){
                            for(int i = 0; i < L; i++)
                                if(map[y+i+1][x+W] == 2) cnt++;
                            for(int i = 0; i < W-1; i++)
                                if(map[y+L][x+i+1] == 2) cnt++;
                            if(cnt < 2){
                                for(int i = 0; i < L; i++){
                                    map[y+i+1][x+W] = 1, map[y+i][x] = 0;
                                }
                                for(int i = 0; i < W; i++){
                                    map[y+L][x+i+1] = 1, map[y][x+i] = 0;
                                }
                                x++, y++;
                            }
                    }
                    break;
        }
 
    }
    return 0;
}