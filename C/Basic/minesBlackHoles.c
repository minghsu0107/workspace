#include <stdio.h>
#include <stdlib.h> // for abs() function
 
int main(){
    int x, y, z; // location of spaceship
    int mx, my, mz, bx, by, bz; // locations of mine and black hole
    int N; // number of instructions
    int b = 0; // a flag, indicating whether the spaceship has already encountered the black hole
 
    // input
    scanf("%d%d%d", &x, &y, &z);
    scanf("%d%d%d %d%d%d", &mx, &my, &mz, &bx, &by, &bz);
    scanf("%d", &N);
 
    // for each instruction
    for(int n = 1; n <= N; n++){
        int m;
        scanf("%d", &m);
 
        // move spaceship according to the direction
        if (m == 1){
            x++;
        }
        else if (m == 2){
            x--;
        }
        else if (m == 3){
            y++;
        }
        else if (m == 4){
            y--;
        }
        else if (m == 5){
            z++;
        }
        else if (m == 6){
            z--;
        }
 
 
        // dist(spaceship, mine) < 10 : explode, don't need to perform the rest of the instructions
        if (abs(x - mx) + abs(y - my) + abs(z - mz) < 10){
            break;
        }
        // dist(spaceship, black hole) < 10 and hasn't encountered the black hole yet : attract by the black hole
        else if (abs(x - bx) + abs(y - by) + abs(z - bz) < 10 && b == 0){
            x = bx, y = by, z = bz;
            b = 1;
        }
 
        // print the location every five steps
        if (n % 5 == 0){
            printf("%d %d %d\n", x, y, z);
        }
    }
 
    return 0;
}