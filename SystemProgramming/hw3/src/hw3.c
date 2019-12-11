#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include "scheduler.h"
#define SIGUSR3 SIGWINCH

static jmp_buf MAIN;
static int P, Q, task, release, mutex = 0;
static int cnt[5];
static struct sigaction newact, oldact;
static sigset_t newmask, oldmask;

extern jmp_buf SCHEDULER;
int idx = 0;
char arr[10000] = {};
FCB_ptr Current = NULL;
FCB_ptr Head = NULL;

void printList(FCB_ptr start) {
	printf("%d %d %d\n", start->Previous->Name, start->Name, start->Next->Name);
	FCB_ptr i = start->Next;
	for (; i != start; i = i->Next)
		printf("%d %d %d\n", i->Previous->Name, i->Name, i->Next->Name);
}

void sig_usr(int signo) {
	if (signo == SIGUSR1) {
		longjmp(SCHEDULER, -3);
	}
	else if (signo == SIGUSR2) {
		mutex = 0;
		longjmp(SCHEDULER, -3);
	}
	else if (signo == SIGUSR3) {
		fflush(stdout);
		longjmp(SCHEDULER, -3);
	}
}

void install_handler() {
	newact.sa_handler = sig_usr;
	sigemptyset(&newact.sa_mask);
	newact.sa_flags = 0;
	sigaction(SIGUSR1, &newact, &oldact);
	sigaction(SIGUSR2, &newact, NULL);
	sigaction(SIGUSR3, &newact, NULL);
}

void set_mask() {
	sigemptyset(&newmask);
	sigaddset(&newmask, SIGUSR1);
	sigaddset(&newmask, SIGUSR2);
	sigaddset(&newmask, SIGUSR3);
	sigprocmask(SIG_BLOCK, &newmask, &oldmask);
}

void funct_1(int name) {
	Current->Next = (FCB_ptr) malloc(sizeof(FCB));
	Current->Next->Previous = Current;
	Current->Next->Name = 1;
	Current = Current->Next;
	int n = setjmp(Current->Environment);
	if (n == 1) {
		if (mutex == 0) {
			if (cnt[1] || task == 1 || task == 3) {
				mutex = 1;
				for (int k = 1; k <= release; ++k) {
					for (int j = 1; j <= Q; ++j) {
						//sleep(1);
						arr[idx++] = '1';
					}
				}
				mutex = 0;
				if (task == 2) {
					--cnt[1];
					longjmp(SCHEDULER, -3);
				}
			}
		}
		longjmp(SCHEDULER, -2);
	}
	else {
		funct_5(name);
	}
}

void funct_2(int name) {
	Current->Next = (FCB_ptr) malloc(sizeof(FCB));
	Current->Next->Previous = Current;
	Current->Next->Name = 2;
	Current = Current->Next;
	int n = setjmp(Current->Environment);
	if (n == 1) {
		if (mutex == 0) {
			if (cnt[2] || task == 1 || task == 3) {
				mutex = 2;
				for (int k = 1; k <= release; ++k) {
					for (int j = 1; j <= Q; ++j) {
						//sleep(1);
						arr[idx++] = '2';
					}
				}
				mutex = 0;
				if (task == 2) {
					--cnt[2];
					longjmp(SCHEDULER, -3);
				}
			}
		}
		longjmp(SCHEDULER, -2);
	}
	else {
		funct_5(name);
	}
}

void funct_3(int name) {
	Current->Next = (FCB_ptr) malloc(sizeof(FCB));
	Current->Next->Previous = Current;
	Current->Next->Name = 3;
	Current = Current->Next;
	int n = setjmp(Current->Environment);
	if (n == 1) {
		if (mutex == 0) {
			if (cnt[3] || task == 1 || task == 3) {
				mutex = 3;
				for (int k = 1; k <= release; ++k) {
					for (int j = 1; j <= Q; ++j) {
						//sleep(1);
						arr[idx++] = '3';
					}
				}
				mutex = 0;
				if (task == 2) {
					--cnt[3];
					longjmp(SCHEDULER, -3);
				}
			}
		}
		longjmp(SCHEDULER, -2);
	}
	else {
		funct_5(name);
	}
}

void funct_4(int name) {
	Current->Next = Head;
	Current->Next->Previous = Current;
	Current->Next->Name = 4;
	Current = Current->Next;
	int n = setjmp(Current->Environment);
	if (n == 1) {
		if (mutex == 0) {
			if (cnt[4] || task == 1 || task == 3) {
				mutex = 4;
				for (int k = 1; k <= release; ++k) {
					for (int j = 1; j <= Q; ++j) {
						//sleep(1);
						arr[idx++] = '4';
					}
				}
				mutex = 0;
				if (task == 2) {
					--cnt[4];
					longjmp(SCHEDULER, -3);
				}
			}
		}
		longjmp(SCHEDULER, -2);
	}
	else {
		longjmp(MAIN, name);
	}
}

void funct_5(int name) {
	int dummy[10000];
	if (name == 1) {
		funct_1(2);
	}
	else if (name == 2) {
		funct_2(3);
	}
	else if (name == 3) {
		funct_3(4);
	}
	else if (name == 4) {
		funct_4(-1);
	}
}

void init() {
	install_handler();
	set_mask();
	Head = (FCB_ptr) malloc(sizeof(FCB));
	Current = Head;
}

void reset() {
	sigaction(SIGUSR1, &oldact, NULL);
	sigaction(SIGUSR2, &oldact, NULL);
	sigaction(SIGUSR3, &oldact, NULL);
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
}

int main(int argc, char *argv[]) {
	init();

	P = (int)strtol(argv[1], NULL, 10);
	Q = (int)strtol(argv[2], NULL, 10);
	task = (int)strtol(argv[3], NULL, 10);
	release = (int)strtol(argv[4], NULL, 10);
	if (task == 2) {
		for (int i = 1; i <= 4; ++i)
			cnt[i] = (int)(P / release);
	}
	else {
		release = P;
	}

	int n = setjmp(MAIN);
	if (n == -1) {
		Scheduler();
		reset();
		exit(0);
	}
	else {
		funct_5(1);
	}
}