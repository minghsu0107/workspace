#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GPA_calculation.h"
int award(int N) {
    return N % 20 == 0? N / 20 : (N / 20) + 1;
}
double Score(char sc[3]) {
    if (!strcmp(sc, "A+")) return 4.3;
    if (!strcmp(sc, "A")) return 4.0;
    if (!strcmp(sc, "A-")) return 3.7;
    if (!strcmp(sc, "B+")) return 3.3;
    if (!strcmp(sc, "B")) return 3.0;
    if (!strcmp(sc, "B-")) return 2.7;
    if (!strcmp(sc, "C+")) return 2.3;
    if (!strcmp(sc, "C")) return 2.0;
    if (!strcmp(sc, "C-")) return 1.7;
    if (!strcmp(sc, "F")) return 0;
}
void countCredits(struct Student *s) {
    int sum = 0;
    for (int i = 0; i < s->N_class; i++) {
        sum += s->all_class[i].academic_credit;
    }
    s->N_credit = sum;
}
void countGPA(struct Student *s) {
    double sum = 0;
    for (int i = 0; i < s->N_class; i++) {
        int k = s->all_class[i].academic_credit;
        double d = Score(s->all_class[i].score);
        sum += k * d;
    }
    s->GPA = sum/s->N_credit;
}
int cmp(double a, double b) {
    if (a - b > 0) return 1;
    else return -1;
}
int cmp1(const void *a, const void *b) {
    struct Student *aa = (struct Student *)a;
    struct Student *bb = (struct Student *)b;
    return cmp(bb->GPA, aa->GPA);
}
int valid(struct Student s) {
    if (s.GPA >= 3.38 && s.N_credit >= 15) 
       return 1;
    else return 0;
}
void GPA_calculation(struct Student all_student[], int N) {
    int numAwards = award(N);
    for (int i = 0; i < N; i++) {
        countCredits(&all_student[i]);
        countGPA(&all_student[i]);
    }
    qsort(all_student, N, sizeof(struct Student), cmp1);
    for (int i = 0; i < numAwards; i++) {
        if (valid(all_student[i])) {
           printf("%d %s %f\n", i+1, all_student[i].name, all_student[i].GPA);
        }
    }
}