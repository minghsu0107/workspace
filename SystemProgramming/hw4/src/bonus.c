#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "threadpool.h"

#define DIMENSION 784
#define LOOP_UNROLL 8
#define TRAINSIZE 60000
#define TESTSIZE 10000
#define ONEHOTCOLS 10

const float eta = 0.1059;
const int iter = 21;

/*
const float eta = 0.055;
const int iter = 50;
*/

typedef struct {
	float x[DIMENSION];
	int y;
} Record;

typedef struct {
	float w[ONEHOTCOLS][DIMENSION];
} Weight;

typedef struct Argu {
    int l, r;
} Argu;

Record *trainingData = NULL;
Record *testData = NULL;
Weight *weight = NULL;

FILE *fp1, *fp2, *fp3;
int n_threads, n_works;
unsigned char buf[TRAINSIZE];

float probs[TRAINSIZE][ONEHOTCOLS];
float probs_trans[ONEHOTCOLS][TRAINSIZE];
float trainingData_trans[DIMENSION][TRAINSIZE];
float grad[ONEHOTCOLS][DIMENSION];
int y_train_onehot[TRAINSIZE][ONEHOTCOLS];

void read_data() {
	for (int i = 0; i < TRAINSIZE; ++i) {
		fread(buf, sizeof(unsigned char), DIMENSION, fp1);
		for (int j = 0; j < DIMENSION; ++j) {
			trainingData[i].x[j] = (float)buf[j] / 255;
		}
	}
	fread(buf, sizeof(unsigned char), TRAINSIZE, fp2);
	for (int i = 0; i < TRAINSIZE; ++i) {
		trainingData[i].y = (int)buf[i];
		y_train_onehot[i][(int)buf[i]] = 1;
	}
	for (int i = 0; i < TESTSIZE; ++i) {
		fread(buf, sizeof(unsigned char), DIMENSION, fp3);
		for (int j = 0; j < DIMENSION; ++j) {
			testData[i].x[j] = (float)buf[j] / 255;
		}
	}
}

void init() {
	trainingData = (Record*)malloc(sizeof(Record) * TRAINSIZE);
	testData = (Record*)malloc(sizeof(Record) * TESTSIZE);
	weight = (Weight*)calloc(1, sizeof(Weight));
}

void prepocess() {
	for (int i = 0; i < DIMENSION; ++i) {
        for (int j = 0; j < TRAINSIZE; ++j) {
            trainingData_trans[i][j] = trainingData[j].x[i];
        }
	}
}

void softmax(float *scores, int N) {
	int i;
    float sum, max;

    for (i = 1, max = scores[0]; i < N; ++i) {
        if (scores[i] > max) {
            max = scores[i];
        }
    }

    for (i = 0, sum = 0; i < N; ++i) {
        scores[i] = exp(scores[i] - max);
        sum += scores[i];
    }

    for (i = 0; i < N; ++i) {
        scores[i] /= sum;
    }
}

float vectorMul(float *a, float *b, int dimension) {
	float sum = 0.0;
	int i;
	for (i = 0; i + LOOP_UNROLL < dimension; i += LOOP_UNROLL) {
		sum += *a * *b, ++a, ++b;
        sum += *a * *b, ++a, ++b;
        sum += *a * *b, ++a, ++b;
        sum += *a * *b, ++a, ++b;
        sum += *a * *b, ++a, ++b;
        sum += *a * *b, ++a, ++b;
        sum += *a * *b, ++a, ++b;
        sum += *a * *b, ++a, ++b;
	}
	for (; i < dimension; ++i)
		sum += *a * *b, ++a, ++b;
	return sum;
}


void get_prob_transpos() {
	for (int i = 0; i < ONEHOTCOLS; ++i) {
        for (int j = 0; j < TRAINSIZE; ++j) {
            probs_trans[i][j] = probs[j][i];
        }
	}
}

void thread_multiply(void *arg) {
    Argu data = * ((Argu *) arg);
    int l = data.l, r = data.r;

    for (int i = l; i <= r; ++i) {
    	for (int j = 0; j < ONEHOTCOLS; ++j) {
			probs[i][j] = vectorMul(weight->w[j], trainingData[i].x, DIMENSION);
		}
		softmax(probs[i], ONEHOTCOLS);
		for (int j = 0; j < ONEHOTCOLS; ++j) {
			probs[i][j] -= y_train_onehot[i][j];
		}
    }
}

void multiclass_classifier() {
	threadpool thpool = thpool_init(n_threads);

    for (int i = 0; i < iter; ++i) {
    	for (int j = 0; j < n_works; ++j) {
	        Argu *data = (Argu *) malloc(sizeof(Argu));
	        data->l = j * TRAINSIZE / n_works;
	        data->r = (j+1) * TRAINSIZE / n_works - 1;
        
        	thpool_add_work(thpool, &thread_multiply, (void *) (data));
    	}
 		thpool_wait(thpool);
		
		get_prob_transpos();
		for (int i = 0; i < ONEHOTCOLS; ++i) {
			for (int j = 0; j < DIMENSION; ++j) {
				grad[i][j] = vectorMul(trainingData_trans[j], probs_trans[i], TRAINSIZE);
			}
		}
		for (int i = 0; i < ONEHOTCOLS; ++i) {
			for (int j = 0; j < DIMENSION; ++j) {
				weight->w[i][j] = weight->w[i][j] - (eta * grad[i][j]);
			}
		}
	}
	thpool_destroy(thpool);
}

void outputCSV(Record *data, int N) {
	FILE *fp = fopen("result.csv", "w");
	fprintf(fp, "id,label\n");
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < ONEHOTCOLS; ++j) {
			probs[i][j] = vectorMul(data[i].x, weight->w[j], DIMENSION);
		}
		softmax(probs[i], ONEHOTCOLS);

		int idx = 0;
		float M = probs[i][0];
		for (int j = 1; j < ONEHOTCOLS; ++j) {
        	if (probs[i][j] > M) {
            	M = probs[i][j];
            	idx = j;
        	}
    	}
    	fprintf(fp, "%d,%d\n", i, idx);
	}
	fclose(fp);
}

void clean() {
	free(trainingData);
	free(testData);
	free(weight);
}

int main(int argc, char *argv[]) {
	
	fp1 = fopen(argv[1], "rb");
	fp2 = fopen(argv[2], "rb");
	fp3 = fopen(argv[3], "rb");
	n_threads = (int)strtol(argv[4], NULL, 10);
	n_works = (int)strtol(argv[4], NULL, 10);

	init();
	read_data();
	prepocess();

    multiclass_classifier();
    outputCSV(testData, TESTSIZE);
    clean();
    return 0;
}
