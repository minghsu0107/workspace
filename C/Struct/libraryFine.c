#include <stdio.h>
enum Type {NOVEL, COMICS, MANUAL, TEXTBOOK};
 
struct Book {
    char title[128];
    enum Type type;
    char ISBN[128];
    char authors[128];
    unsigned int importance;
};

struct Date {
    unsigned int year;
    unsigned int month;
    unsigned int day;
};

static int addDay[] = {0, 0, 31, 59, 90, 120, 151,
                181, 212, 243, 273, 304,
                334, 365};
static int mDay[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int cntDay(int y, int m, int d) {
    int sum, leap, isleap;
    isleap = (y%4 == 0 && y%100 != 0) || y%400 == 0;
    y--;
    leap = y/4 - y/100 + y/400;
    sum = y*365 + leap + addDay[m] + (m > 2)*isleap + d;
    return sum;
}
static int rental_time(enum Type t) {
	switch(t) {
		case NOVEL: 	return 90;
		case COMICS: 	return 10;
		case MANUAL: 	return 100;
		case TEXTBOOK: 	return 5;
	}
	return -1;
}
static int compute_dist(unsigned int n) {
	// __builtin_ffs(n) returns i, where i - 1 is the location of first 1 counting from LSB
	// ex: n = 00000000-00000000-00000010-00101000, then i = 4, i - 1 = 3
	int a = __builtin_ffs(n) - 1;
	int b = __builtin_ffs(n ^ (1LU<<a)) - 1;
	return b - a - 1;
}
unsigned int library_fine(struct Book book, struct Date date_borrowed, struct Date date_returned) {
	int days = - cntDay(date_borrowed.year, date_borrowed.month, date_borrowed.day) 
			 + cntDay(date_returned.year, date_returned.month, date_returned.day) + 1;
	int mx = rental_time(book.type);
	if (days <= mx)	return 0;
	int cost = compute_dist(book.importance);
	return (days - mx) * cost;
}
int main(){
    struct Book book = {
        "Neon Genesis Evangelion",
        COMICS,
        "978-159-116-400-5",
        "Yoshiyuki Sadamoto",
        17
    };
    struct Date date_borrowed, date_returned;
    date_borrowed.year  = 2007;
    date_borrowed.month = 11;
    date_borrowed.day   = 14;
    date_returned.year  = 2007;
    date_returned.month = 12;
    date_returned.day   = 3;
    printf("The fine is $%d.\n", library_fine(book, date_borrowed, date_returned));
    return 0;
}
