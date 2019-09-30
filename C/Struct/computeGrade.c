#include "computeGrade.h"
#include <stdio.h>
double computAvg(Classes c, int idx) {
	double sum = 0;
	for (int i = 0; i < c.numStudent; i++) {
		sum += c.student[i].score[idx].rawScore;
	}
    return sum/c.numStudent;
}
void adjust(Classes *c1, Classes *c2, double r, int idx) {
    for (int i = 0; i < c1->numStudent; i++) {
    	c1->student[i].score[idx].scaledScore = 
    	((double)(c1->student[i].score[idx].rawScore)) * r;
    	if (c1->student[i].score[idx].scaledScore > 100) 
    		c1->student[i].score[idx].scaledScore = 100;
    }
    for (int i = 0; i < c2->numStudent; i++) {
    	c2->student[i].score[idx].scaledScore = 
    	c2->student[i].score[idx].rawScore;
    }
}
void computeFinal(Classes *c) {
	for (int j = 0; j < c->numStudent; j++) {
		double sum = 0;
		for (int k = 0; k < 18; k++) {
			sum += c->student[j].score[k].scaledScore;
		}
		c->student[j].finalScore = sum * 0.06;
		if (c->student[j].finalScore > 100)
			c->student[j].finalScore = 100;
	}
}
void computeGrade(Classes classes[2]) {
	for (int i = 0; i < 18; i++) {
		double avg1 = computAvg(classes[0], i), avg2 = computAvg(classes[1], i);
		if (avg1 < avg2) adjust(&classes[0], &classes[1], avg2 / avg1, i);
		else adjust(&classes[1], &classes[0], avg1 / avg2, i);
    }
    for (int i = 0; i < 2; i++) {
    	computeFinal(&classes[i]);
    	for (int j = 0; j < classes[i].numStudent; j++)
    		printf("%s %f\n", classes[i].student[j].id, classes[i].student[j].finalScore);
    }
}