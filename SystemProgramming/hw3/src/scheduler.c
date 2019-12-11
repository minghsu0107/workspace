#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

extern int idx;
extern char arr[10000];
jmp_buf SCHEDULER = {};

void Scheduler() {
	int n, c;
	n = setjmp(SCHEDULER);
	if (n == -2) {
		if (Current->Next == Current) {
			arr[idx] = '\0';
			printf("%s\n", arr);
			fflush(stdout);
			exit(0);
		}
		else {
			Current->Next->Previous = Current->Previous;
			Current->Previous->Next = Current->Next;
		}
	}
	Current = Current->Next;
	longjmp(Current->Environment, 1);
}