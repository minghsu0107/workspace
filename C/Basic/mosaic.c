#include <stdio.h>
// find the number of 1x1 squares in a given triangle
int main(){
    int x1, y1, x2, y2, x3, y3; // three corners
    int minx, maxx, miny, maxy; // min and max coordinates
    int cx, cy; // the current point being checked
    int cnt = 0; // number of squares in the triangle
 
    scanf("%d%d %d%d %d%d", &x1, &y1, &x2, &y2, &x3, &y3);
 
    minx = (x1 <= x2 && x1 <= x3) ? x1 : (x2 < x3 ? x2 : x3);
    maxx = (x1 >= x2 && x1 >= x3) ? x1 : (x2 > x3 ? x2 : x3);
    miny = (y1 <= y2 && y1 <= y3) ? y1 : (y2 < y3 ? y2 : y3);
    maxy = (y1 >= y2 && y1 >= y3) ? y1 : (y2 > y3 ? y2 : y3);
 
    // for each point in the range
    for(int x = minx; x <= maxx; x++){
        for(int y = miny; y <= maxy; y++){
            // check the 4 coordinates
            for(int c = 0; c < 4; c++){
                if (c == 0){ //left top (x, y)
                    cx = x, cy = y;
                }
                else if (c == 1){ //right top (x+1, y)
                    cx = x + 1, cy = y;
                }
                else if (c == 2){ //left bottom (x, y-1)
                    cx = x, cy = y - 1;
                }
                else if (c == 3){ //right bottom (x+1, y-1)
                    cx = x + 1, cy = y - 1;
                }
 
                // cross product (x1-cx,y1-cy,0) x (x2-cx,y2-cy,0)
                int p1 = (x1 - cx) * (y2 - cy) - (y1 - cy) * (x2 - cx);
                int p2 = (x2 - cx) * (y3 - cy) - (y2 - cy) * (x3 - cx);
                int p3 = (x3 - cx) * (y1 - cy) - (y3 - cy) * (x1 - cx);
 
                // check if same direction
                if (!((p1 >= 0 && p2 >= 0 && p3 >= 0) || (p1 <= 0 && p2 <= 0 && p3 <= 0))){
                    break; // if not, break
                }
 
                // increase count if all 4 corners are inside the triangle
                if (c == 3){
                    cnt++;
                }
            }
        }
    }
 
    printf("%d\n", cnt);
    return 0;
}