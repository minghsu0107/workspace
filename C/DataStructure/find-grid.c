#include <stdio.h>
#include <stdlib.h>

typedef struct City {
    int label;
    struct City *east, *north;
} City; 
void move(City* city, int* pass, int* sum) {
    if(*(pass + city->label))
        return;
 
    *(pass + city->label) = 1;
    if(city->east != NULL && city->north != NULL) {
        if(city->east->north != NULL && city->north->east != NULL)
            ++(*sum);
        move(city->east, pass, sum);
        move(city->north, pass, sum);
    }
    else if(city->east != NULL)
        move(city->east, pass, sum);
    else if(city->north != NULL)
        move(city->north, pass, sum);
}
 
int City_Grid(City *capital) {
    int passed[10000] = {0};
    int N = 0;
    move(capital, passed, &N);
    return N;
}
City* newNode(int label, City *E, City *N) {
    City *u = (City *) malloc(sizeof(City));
    u->label = label, u->east = E, u->north = N;
    return u;
}
 
int main() {
    City *capital = newNode(0, NULL, NULL);
    capital->east = newNode(1, newNode(3, NULL, NULL), NULL);
    capital->north = newNode(2, NULL, newNode(5, NULL, NULL));
    capital->east->north = capital->north->east = newNode(4, NULL, NULL);
 
    City *temp = capital->east->north;
    temp->east = newNode(6, NULL, NULL);
    temp->north = newNode(7, NULL, NULL);
    temp->east->north = temp->north->east = newNode(8, NULL, NULL);
 
    printf("%d\n", City_Grid(capital));
    return 0;
}