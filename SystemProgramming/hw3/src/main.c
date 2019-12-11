#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "scheduler.h"
#define MAXN 15
#define errExit(a) { perror(a); exit(1); }
#define SIGUSR3 SIGWINCH

static int P, Q, task, release, num_signals;
static int signals[MAXN], Fd[2];
static char arg1[MAXN], arg2[MAXN], arg3[MAXN], arg4[MAXN];

void init_input() {
	scanf("%d%d", &P, &Q);
	scanf("%d", &num_signals);
	for (int i = 0; i < num_signals; ++i)
		scanf("%d", &signals[i]);
	task = 3;
	release = 0;
	sprintf(arg1, "%d", P);
	sprintf(arg2, "%d", Q);
	sprintf(arg3, "%d", task);
	sprintf(arg4, "%d", release);

	if (Fd[1] != STDOUT_FILENO) {
		if (dup2(Fd[1], STDOUT_FILENO) != STDOUT_FILENO)
			errExit("dup2");
		close(Fd[1]);
	}
}

void handle_signals() {

}

int main() {
	init_input();
	int child_pid, wpid;
	if ((child_pid = fork()) < 0) {
		errExit("fork");
	}
	else if (child_pid == 0) {
		char *args[] = {"./hw3", arg1, arg2, arg3, arg4, NULL};
		execve("hw3", args, NULL);
	}
	handle_signals();
	while ((wpid = wait(NULL)) > 0);
	exit(0);
}