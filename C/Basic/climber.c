#include <stdio.h>
void travel(int map[1024][1024], int N, int M, int A_r, int A_c, int B_r, int B_c, int directionA[], int directionB[]) {
 
  // direction = {r,c}
    int directions[8][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}, {1,1}, {-1,-1}, {-1,1}, {1,-1}};
 
    int traveled[N][M];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            traveled[i][j] = 0;
        }
    }
 
  traveled[A_r][A_c] = 1;
  traveled[B_r][B_c] = 1;
 
    int stop_A = 0, stop_B = 0; // if travelers are stop
    int steps_A = 0, steps_B = 0;
    while(!(stop_A && stop_B)) {
        int tmp_r, tmp_c;
        int dc_A = -1, dc_B = -1; //the direction of A, B;
 
        if (!stop_A) {
            int mac_height = map[A_r][A_c];
            for(int i = 0; i < 8; i++) {
                tmp_r = A_r + directions[i][0];
                tmp_c = A_c + directions[i][1];
                if (tmp_r >= N || tmp_c >= M || tmp_r < 0 || tmp_c < 0)
                    continue;
                if (map[tmp_r][tmp_c] > mac_height) {
                    mac_height = map[tmp_r][tmp_c];
                    dc_A = i;
                }
            }
 
            directionA[steps_A] = dc_A; // go first
            A_r += (dc_A == -1)? 0 : directions[dc_A][0];
            A_c += (dc_A == -1)? 0 : directions[dc_A][1];
            stop_A = (dc_A == -1)? 1:0; // cannot find the higher hill
            steps_A++;
            if (traveled[A_r][A_c]) {
                directionA[steps_A] = -1;
                stop_A = 1;
            } else {
                traveled[A_r][A_c] = 1;
            }
        }
        if (!stop_B) {
            int min_height = map[B_r][B_c];
            for(int i = 0; i < 8; i++) {
                tmp_r = B_r + directions[i][0];
                tmp_c = B_c + directions[i][1];
                if (tmp_r >= N || tmp_c >= M || tmp_r < 0 || tmp_c < 0)
                    continue;
                if (map[tmp_r][tmp_c] < min_height) {
                    min_height = map[tmp_r][tmp_c];
                    dc_B = i;
                }
            }
 
            directionB[steps_B] = dc_B;
            B_r += (dc_B == -1)? 0 : directions[dc_B][0];
            B_c += (dc_B == -1)? 0 : directions[dc_B][1];
            stop_B = (dc_B == -1)? 1:0; // cannot find the lower hill
            steps_B++;
            if (traveled[B_r][B_c]) {
                directionB[steps_B] = -1;
                stop_B = 1;
            } else {
                traveled[B_r][B_c] = 1;
            }
        }
        // if they meet each other
        if ( A_r == B_r && A_c == B_c ){
            directionA[steps_A] = directionB[steps_B] = -1;
            stop_A = stop_B = 1;
        }
    }
}
int main() {
    int N, M;
    int map[1024][1024];
    int A_r, A_c, B_r, B_c;
    int directionA[1024], directionB[1024];
 
    scanf("%d%d", &N, &M);
 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            scanf("%d", &map[i][j]);
        }
    }
 
    scanf("%d%d%d%d", &A_r, &A_c, &B_r, &B_c);
 
    travel(map, N, M, A_r, A_c, B_r, B_c, directionA, directionB);
 
    int i = 0;
    while (directionA[i] != -1) {
        printf("%d ", directionA[i]);
        i++;
    }
    printf("-1\n");
    i = 0;
    while (directionB[i] != -1) {
        printf("%d ", directionB[i]);
        i++;
    }
    printf("-1\n");
 
    return 0;
}
