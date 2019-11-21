#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include "my_header.h"

FILE *fp;
static int l = 0;
static int r = 1;
int l_downFd[2], l_upFd[2], r_downFd[2], r_upFd[2];
int players[MAXN], host_id, random_key, depth, l_id, l_money, r_id, r_money;
char buf[MAXBUF], arg1[MAXBUF], arg2[MAXBUF], arg3[MAXBUF], arg4[MAXBUF];

void init(int depth) {
	if (pipe(l_downFd) < 0)
		errExit("pipe");
	if (pipe(l_upFd) < 0)
		errExit("pipe");
	if (pipe(r_downFd) < 0)
		errExit("pipe");
	if (pipe(r_upFd) < 0)
		errExit("pipe");
}

void read_players(int host_id, int depth) {
	if (depth == 0) {
		sprintf(buf, "/tmp/Host%d.FIFO", host_id);
		fp = fopen(buf, "r");
		fseek(fp, 0, SEEK_SET);
		fscanf(fp, "%d %d %d %d %d %d %d %d", &players[0], &players[1], 
			   &players[2], &players[3], &players[4], &players[5], 
			   &players[6], &players[7]);
	}
	else if (depth == 1) {
		scanf("%d %d %d %d", &players[0], &players[1], 
			  &players[2], &players[3]);
	}
	else if (depth == 2) {
		scanf("%d %d", &players[0], &players[1]);
	}
}

void redirectIO(int direction) {
	if (direction == 0) {
		if (l_downFd[0] != STDIN_FILENO) {
			if (dup2(l_downFd[0], STDIN_FILENO) != STDIN_FILENO)
				errExit("dup2");
			close(l_downFd[0]);
		}
		if (l_upFd[1] != STDOUT_FILENO) {
			if (dup2(l_upFd[1], STDOUT_FILENO) != STDOUT_FILENO)
				errExit("dup2");
			close(l_upFd[1]);
		}
	}
	else if (direction == 1) {
		if (r_downFd[0] != STDIN_FILENO) {
			if (dup2(r_downFd[0], STDIN_FILENO) != STDIN_FILENO)
				errExit("dup2");
			close(r_downFd[0]);
		}
		if (r_upFd[1] != STDOUT_FILENO) {
			if (dup2(r_upFd[1], STDOUT_FILENO) != STDOUT_FILENO)
				errExit("dup2");
			close(r_upFd[1]);
		}
	}
}

void execSubHost(int host_id, int random_key, int depth, int direction) {
	redirectIO(direction);
	sprintf(arg1, "%d", host_id);
	sprintf(arg2, "%d", random_key);
	sprintf(arg3, "%d", depth);
	char *args[] = {"./host", arg1, arg2, arg3, NULL};
	execve("host", args, NULL);
}

void execPlayer(int direction) {
	redirectIO(direction);
	sprintf(arg1, "%d", players[0 + direction]);
	char *args[] = {"./player", arg1, NULL};
	execve("player", args, NULL);
}

void runHost(int host_id, int depth, int direction) {
	if (direction == 0) {
		if (depth == 0) {
			dprintf(l_downFd[1], "%d %d %d %d\n", players[0], players[1],
				    players[2], players[3]);
			fsync(l_downFd[1]);
		}
		else if (depth == 1) {
			dprintf(l_downFd[1], "%d %d\n", players[0], players[1]);
			fsync(l_downFd[1]);
		}
		else if (depth == 2) {
			read(l_upFd[0], buf, sizeof(buf));
			sscanf(buf, "%d %d", &l_id, &l_money);
			fprintf(stderr, "%d %d\n", l_id, l_money);
		}
	}
	else if (direction == 1) {
		if (depth == 0) {
			dprintf(r_downFd[1], "%d %d %d %d\n", players[4], players[5],
				    players[6], players[7]);
			fsync(r_downFd[1]);
		}
		else if (depth == 1) {
			dprintf(r_downFd[1], "%d %d\n", players[2], players[3]);
			fsync(r_downFd[1]);
		}
		else if (depth == 2) {
			read(r_upFd[0], buf, sizeof(buf));
			sscanf(buf, "%d %d", &r_id, &r_money);
			fprintf(stderr, "%d %d\n", r_id, r_money);
		}
	}
}

void run(int host_id, int random_key, int depth) {
	read_players(host_id, depth);

	int child_pid, wpid;
	if (depth == 0) {
		if ((child_pid = fork()) < 0) {
			errExit("fork");
		}
		else if (child_pid == 0) {
			execSubHost(host_id, random_key, depth + 1, l);
		}

		if ((child_pid = fork()) < 0) {
			errExit("fork");
		}
		else if (child_pid == 0) {
			execSubHost(host_id, random_key, depth + 1, r);
		}
	}
	else if (depth == 1) {
		if ((child_pid = fork()) < 0) {
			errExit("fork");
		}
		else if (child_pid == 0) {
			execSubHost(host_id, random_key, depth + 1, l);
		}

		if ((child_pid = fork()) < 0) {
			errExit("fork");
		}
		else if (child_pid == 0) {
			execSubHost(host_id, random_key, depth + 1, r);
		}
	}
	else if (depth == 2) {
		if ((child_pid = fork()) < 0) {
			errExit("fork");
		}
		else if (child_pid == 0) {
			execPlayer(l);
		}

		if ((child_pid = fork()) < 0) {
			errExit("fork");
		}
		else if (child_pid == 0) {
			execPlayer(r);
		}
	}
	runHost(host_id, depth, l);
	runHost(host_id, depth, r);
	while ((wpid = wait(NULL)) > 0);
}

int main(int argc, char *argv[]) {
	host_id = (int)strtol(argv[1], NULL, 10);
	random_key = (int)strtol(argv[2], NULL, 10);
	depth = (int)strtol(argv[3], NULL, 10);
	init(depth);
	run(host_id, random_key, depth);
	exit(0);
}