#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>
#include <assert.h>
#include "scheduler.h"
#define errExit(a) { perror(a); exit(1); }
#define SIGUSR3 SIGWINCH
#define NUMFUNC 4
#define MAXBUF 1000

static jmp_buf MAIN;
static int P, Q, task, release, mutex = 0, ack = 1;
static int cnt[NUMFUNC + 1];
static char buf[MAXBUF];
static struct sigaction newact, oldact;
static sigset_t newmask, oldmask, pendmask;
static volatile sig_atomic_t ptr[NUMFUNC] = {1, 1, 1, 1};
static volatile FCB_ptr tmp_fcb = NULL;

extern jmp_buf SCHEDULER;
int idx = 0;
char arr[10000] = {};
FCB_ptr Current = NULL;
FCB_ptr Head = NULL;

void printList(FCB_ptr start) {
	assert (start->Next != NULL);

	int len = 1;
	sprintf(buf, "%d", start->Next->Name);
	FCB_ptr i = start->Next->Next;
	for (; i != start; i = i->Next) {
		if (ptr[i->Name - 1] == 1) {
			sprintf(buf + len, " %d", i->Name);
			len += 2;
		}
	}
	buf[len++] = '\n';
	buf[len] = '\0';
	write(STDOUT_FILENO, buf, sizeof(buf));
}

void sig_usr(int signo) {
	if (signo == SIGUSR1) {
		write(STDOUT_FILENO, &ack, sizeof(int));

		sigprocmask(SIG_BLOCK, &newmask, NULL);
		longjmp(SCHEDULER, -3);
	}
	else if (signo == SIGUSR2) {
		write(STDOUT_FILENO, &ack, sizeof(int));

		sigprocmask(SIG_BLOCK, &newmask, NULL);
		longjmp(SCHEDULER, -3);
	}
	else if (signo == SIGUSR3) {
		write(STDOUT_FILENO, &ack, sizeof(int));
		printList(Current);

		tmp_fcb = Current->Next;
		Current->Next = Current;
		sigprocmask(SIG_BLOCK, &newmask, NULL);
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

void check_sigpending() {
	if (sigpending(&pendmask) < 0)
		errExit("sigpending");
	int mes1, mes2, mes3;
	mes1 = sigismember(&pendmask, SIGUSR1);
	mes2 = sigismember(&pendmask, SIGUSR2);
	mes3 = sigismember(&pendmask, SIGUSR3);
	if (mes1 > 0 || mes2 > 0 || mes3 > 0) {
		if (mes2 > 0)
			mutex = 0;
		sigprocmask(SIG_SETMASK, &oldmask, NULL);
	}
}

void funct_1(int name) {
	Current->Next = (FCB_ptr) malloc(sizeof(FCB));
	Current->Next->Previous = Current;
	Current->Next->Name = 1;
	Current = Current->Next;
	int n = setjmp(Current->Environment);
	if (n == 1) {
		if (tmp_fcb != NULL) {
			Current->Next = tmp_fcb;
			tmp_fcb = NULL;
		}
		if (mutex == 0 || mutex == 1) {
			if (cnt[1] || task == 1 || task == 3) {
				mutex = 1;
				while (ptr[0] <= release) {
					for (int j = 1; j <= Q; ++j) {
						sleep(1);
						arr[idx++] = '1';
					}
					++ptr[0];
					if (task == 3)
						check_sigpending();
				}
				mutex = 0;
				
				if (cnt[1] != 0) {
					--cnt[1];
					ptr[0] = 1;
					longjmp(SCHEDULER, -3);
				}
			}
			longjmp(SCHEDULER, -2);
		}
		else {
			longjmp(SCHEDULER, -3);
		}
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
		if (tmp_fcb != NULL) {
			Current->Next = tmp_fcb;
			tmp_fcb = NULL;
		}
		if (mutex == 0 || mutex == 2) {
			if (cnt[2] || task == 1 || task == 3) {
				mutex = 2;
				while (ptr[1] <= release) {
					for (int j = 1; j <= Q; ++j) {
						sleep(1);
						arr[idx++] = '2';
					}
					++ptr[1];
					if (task == 3)
						check_sigpending();
				}
				mutex = 0;
				
				if (cnt[2] != 0) {
					--cnt[2];
					ptr[1] = 1;
					longjmp(SCHEDULER, -3);
				}
			}
			longjmp(SCHEDULER, -2);
		}
		else {
			longjmp(SCHEDULER, -3);
		}
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
		if (tmp_fcb != NULL) {
			Current->Next = tmp_fcb;
			tmp_fcb = NULL;
		}
		if (mutex == 0 || mutex == 3) {
			if (cnt[3] || task == 1 || task == 3) {
				mutex = 3;
				while (ptr[2] <= release) {
					for (int j = 1; j <= Q; ++j) {
						sleep(1);
						arr[idx++] = '3';
					}
					++ptr[2];
					if (task == 3)
						check_sigpending();
				}
				mutex = 0;
				
				if (cnt[3] != 0) {
					--cnt[3];
					ptr[2] = 1;
					longjmp(SCHEDULER, -3);
				}
			}
			longjmp(SCHEDULER, -2);
		}
		else {
			longjmp(SCHEDULER, -3);
		}
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
		if (tmp_fcb != NULL) {
			Current->Next = tmp_fcb;
			tmp_fcb = NULL;
		}
		if (mutex == 0 || mutex == 4) {
			if (cnt[4] || task == 1 || task == 3) {
				mutex = 4;
				while (ptr[3] <= release) {
					for (int j = 1; j <= Q; ++j) {
						sleep(1);
						arr[idx++] = '4';
					}
					++ptr[3];
					if (task == 3)
						check_sigpending();
				}
				mutex = 0;
				
				if (cnt[4] != 0) {
					--cnt[4];
					ptr[3] = 1;
					longjmp(SCHEDULER, -3);
				}
			}
			longjmp(SCHEDULER, -2);
		}
		else {
			longjmp(SCHEDULER, -3);
		}
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
	memset(cnt, 0, sizeof(cnt));
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