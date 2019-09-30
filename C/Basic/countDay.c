#include <stdio.h>
//寫一個函式 count_day 來計算某個特定的月份裡 星期日 星期一 ... 星期六 各有幾天.
//要計算某一天為星期幾，可以由一月一號星期幾的數字加上那一天之前的天數後，取 Mod 7 得到.
void count_day(int year, int day, int month, int results[7]){
    int daysOfMonths[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, i;
    results[0] = results[1] = results[2] = results[3] = results[4] = results[5] = results[6] = 0;
    if( (year % 400 == 0) || ( year % 4 == 0 && year % 100 != 0) )
        ++daysOfMonths[2];
 
    for( i=1 ; i < month ; ++i )
        day += daysOfMonths[i];
 
    for( i=0 ; i < daysOfMonths[month] ; ++i )
        ++results[ (day+i) % 7 ];
}
int main(){
    int year, day, month, results[7] = {0}, i;
 
    while(scanf("%d %d %d", &year, &day, &month) == 3){
        for(i = 0; i < 7; i++)
            results[i] = 0;
        count_day(year, day, month, results);
        for(i = 0; i < 6; i++)
            printf("%d ", results[i]);
        printf("%d\n", results[i]);
    }
    return 0;
}