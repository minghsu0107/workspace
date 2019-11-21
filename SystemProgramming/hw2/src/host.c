#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include "my_header.h"

FILE *fp1, *fp2;
static int l = 0;
static int r = 1;
static int batch = 8;
int l_downFd[2], l_upFd[2], r_downFd[2], r_upFd[2];
int players[MAXN];
int host_id, random_key, depth, l_id, l_money, r_id, r_money, winner_id, winner_money;
char buf[MAXBUF], arg1[MAXBUF], arg2[MAXBUF], arg3[MAXBUF], arg4[MAXBUF];

void init() {
	if (depth == 0) {
		sprintf(buf, "./Host%d.FIFO", host_id);
		fp1 = fopen(buf, "r");
		sprintf(buf, "./Host.FIFO");
		fp2 = fopen(buf, "w+");
	}
	if (pipe(l_downFd) < 0)
		errExit("pipe");
	if (pipe(l_upFd) < 0)
		errExit("pipe");
	if (pipe(r_downFd) < 0)
		errExit("pipe");
	if (pipe(r_upFd) < 0)
		errExit("pipe");
}
void read_players() {
	if (depth == 0) {
		fscanf(fp1, "%d %d %d %d %d %d %d %d", &players[0], &players[1], 
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
		}
		if (l_upFd[1] != STDOUT_FILENO) {
			if (dup2(l_upFd[1], STDOUT_FILENO) != STDOUT_FILENO)
				errExit("dup2");
		}
	}
	else if (direction == 1) {
		if (r_downFd[0] != STDIN_FILENO) {
			if (dup2(r_downFd[0], STDIN_FILENO) != STDIN_FILENO)
				errExit("dup2");
		}
		if (r_upFd[1] != STDOUT_FILENO) {
			if (dup2(r_upFd[1], STDOUT_FILENO) != STDOUT_FILENO)
				errExit("dup2");
		}
	}
}

void execSubHost(int depth, int direction) {
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

void allocatePlayers(int direction) {
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
	}
}
/*
dprintf(l_downFd[1], "%d\n", winner_id);
dprintf(r_downFd[1], "%d\n", winner_id);
*/

void outputResults(FILE *fp) {
	fprintf(fp, "%d\n", random_key);
	for (int i = 0; i < batch; ++i) {
		if (players[i] == winner_id) {
			fprintf(fp, "%d %d\n", players[i], 1);
		}
		else {
			fprintf(fp, "%d %d\n", players[i], 2);
		}
	}
	fprintf(fp, "\n");
    fflush(fp);
}

void judge() {
	read(l_upFd[0], buf, sizeof(buf));
	sscanf(buf, "%d %d", &l_id, &l_money);
	read(r_upFd[0], buf, sizeof(buf));
	sscanf(buf, "%d %d", &r_id, &r_money);

	int tmp_id, tmp_money;
	if (l_money > r_money) {
		tmp_id = l_id;
		tmp_money = l_money;
	}
	else {
		tmp_id = r_id;
		tmp_money = r_money;
	}

	if (depth == 0) {
		winner_id = tmp_id;
		winner_money = tmp_money;
		outputResults(fp2);
		//fprintf(stderr, "winner: %d %d\n", winner_id, winner_money);
	}
	else {
		printf("%d %d\n", tmp_id, tmp_money);
	}
}
/*
void sendStopMessage(int depth, int direction) {
	if (direction == 0) {
		if (depth == 0) {
			dprintf(l_downFd[1], "-1 -1 -1 -1\n");
			fsync(l_downFd[1]);
		}
		else if (depth == 1) {
			dprintf(l_downFd[1], "-1 -1\n");
			fsync(l_downFd[1]);
		}
		close(l_downFd[1]);
		close(l_upFd[0]);
	}
	else if (direction == 1) {
		if (depth == 0) {
			dprintf(r_downFd[1], "-1 -1 -1 -1\n");
			fsync(r_downFd[1]);
		}
		else if (depth == 1) {
			dprintf(r_downFd[1], "-1 -1\n");
			fsync(r_downFd[1]);
		}
		close(r_downFd[1]);
		close(r_upFd[0]);
	}
}
*/
void run() {
	int child_pid, wpid;
	if (depth == 2) {
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
	else {
		if ((child_pid = fork()) < 0) {
			errExit("fork");
		}
		else if (child_pid == 0) {
			execSubHost(depth + 1, l);
		}

		if ((child_pid = fork()) < 0) {
			errExit("fork");
		}
		else if (child_pid == 0) {
			execSubHost(depth + 1, r);
		}
	}
	allocatePlayers(l);
	allocatePlayers(r);
	judge();
	while ((wpid = wait(NULL)) > 0);
}

int main(int argc, char *argv[]) {
	host_id = (int)strtol(argv[1], NULL, 10);
	random_key = (int)strtol(argv[2], NULL, 10);
	depth = (int)strtol(argv[3], NULL, 10);

	init();
	read_players();
	run();
	exit(0);
	
	/*
	for (int i = 0; i < 1; ++i) {
		read_players();
		
		if (players[0] == -1) {
			if (depth == 0) {
				fclose(fp1);
				fclose(fp2);
			}
			else {
				close(STDIN_FILENO);
				close(STDOUT_FILENO);
			}
			sendStopMessage(depth, l);
			sendStopMessage(depth, r);
			fprintf(stderr, "end!\n");
			exit(0);
		}
		run();
	}*/
}