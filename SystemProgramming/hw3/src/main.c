#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "scheduler.h"
#define MAXN 15
#define MAXNUMSIG 15
#define MAXBUF 1000
#define errExit(a) { perror(a); exit(1); }
#define SIGUSR3 SIGWINCH

static int P, Q, task, release, num_signals, tmp, ack;
static int signals[MAXN], pipeFd[2];
static int SIG[3] = {SIGUSR1, SIGUSR2, SIGUSR3};
static char arg1[MAXN], arg2[MAXN], arg3[MAXN], arg4[MAXN];
static char buf[MAXBUF];

void init() {
	scanf("%d%d", &P, &Q);
	scanf("%d", &num_signals);
	for (int i = 0; i < num_signals; ++i) {
		scanf("%d", &tmp);
		signals[i] = SIG[tmp - 1];
	}
	task = 3;
	release = 0;
	sprintf(arg1, "%d", P);
	sprintf(arg2, "%d", Q);
	sprintf(arg3, "%d", task);
	sprintf(arg4, "%d", release);

	if (pipe(pipeFd) < 0)
		errExit("pipe");
}

void handle_signals(int child_pid) {
	for (int i = 0; i < num_signals; ++i) {
		sleep(5);
		kill(child_pid, signals[i]);
		read(pipeFd[0], &ack, sizeof(int));
		if (signals[i] == SIG[2]) {
			read(pipeFd[0], buf, sizeof(buf));
			printf("%s", buf);
			fflush(stdout);
		}
	}
}

int main() {
	init();
	
	int child_pid, wpid;
	if ((child_pid = fork()) < 0) {
		errExit("fork");
	}
	else if (child_pid == 0) {
		if (pipeFd[1] != STDOUT_FILENO) {
			if (dup2(pipeFd[1], STDOUT_FILENO) != STDOUT_FILENO)
				errExit("dup2");
			close(pipeFd[1]);
		}
		close(pipeFd[0]);
		char *args[] = {"./hw3", arg1, arg2, arg3, arg4, NULL};
		execve("hw3", args, NULL);
	}
	else {
		close(pipeFd[1]);
		handle_signals(child_pid);

		read(pipeFd[0], buf, sizeof(buf));
		while ((wpid = wait(NULL)) > 0);
		close(pipeFd[0]);

		printf("%s", buf);
		fflush(stdout);
		exit(0);
	}
}