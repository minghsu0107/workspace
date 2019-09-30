#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAXN 100
#define MAXL 25
typedef struct {
    char book_title[MAXL], author[MAXL];
}BookAuthor;
 
typedef struct {
    char book_title[MAXL];
    int selling, date;
}BookSelling;

typedef struct {
    char book_title[MAXL], author[MAXL];
    int selling, date;
}BookInfo;

typedef struct {
    int num; // the number of BookInfo
    BookInfo books[MAXN];
}BookInfoList;
 
// compare function for qsort
int cmp(const void *p, const void *q){
    BookInfo info_p = *(BookInfo*) p, info_q = *(BookInfo*)q;
    int x = strcmp(info_p.book_title, info_q.book_title);
    return x == 0 ? info_p.date > info_q.date : x;
}
 
 
BookInfoList merge(int N, int M, BookAuthor authorArr[], BookSelling sellingArr[]){
    BookInfoList infoList;
    int n = 0;
 
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){
            if (strcmp(authorArr[j].book_title, sellingArr[i].book_title) == 0){
                strcpy(infoList.books[n].book_title, authorArr[j].book_title);
                strcpy(infoList.books[n].author, authorArr[j].author);
                infoList.books[n].selling = sellingArr[i].selling;
                infoList.books[n].date = sellingArr[i].date;
                n++;
                break;
            }
        }
    }
 
    qsort(infoList.books, n, sizeof(infoList.books[0]), cmp);
 
 
    /*for (int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            int x = strcmp(infoList.books[i].book_title, infoList.books[j].book_title);
            if ( x > 0 || (x == 0 && infoList.books[i].date > infoList.books[j].date)){
                BookInfo info = infoList.books[i];
                infoList.books[i] = infoList.books[j];
                infoList.books[j] = info;
            }
        }
    }*/
 
    infoList.num = n;
    return infoList;
}
int main(){
    int N, M;
    BookAuthor authorArr[MAXN];
    BookSelling sellingArr[MAXN];
 
    assert(scanf("%d %d", &N, &M) == 2);
    for(int i = 0; i < N; i++)
        assert(scanf("%s %s", authorArr[i].book_title,
                              authorArr[i].author) == 2);
 
    for(int i = 0; i < M; i++)
        assert(scanf("%s %d %d", sellingArr[i].book_title,
                                 &sellingArr[i].selling,
                                 &sellingArr[i].date) == 3);
 
    BookInfoList result = merge(N, M, authorArr, sellingArr);
 
    for(int i = 0; i < result.num; i++)
        printf("%s %s %d %d\n", result.books[i].book_title,
                                result.books[i].author,
                                result.books[i].date, result.books[i].selling);
 
    return 0;
}
