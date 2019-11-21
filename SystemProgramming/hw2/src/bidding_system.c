#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include "my_header.h"

int tmp[MAXN], scores[MAXN], idx[MAXN], dummy, key, _;
FILE *fp;
int random_key[MAXHOST], hosts[MAXRAND];
char FIFO[MAXHOST][MAXBUF], buf[MAXBUF];
char arg1[MAXBUF], arg2[MAXBUF], arg3[MAXBUF];

BidSystem bid;
Host host;

void com(int d, int len) {  
    if (len == bid.batch) {  
        for (int i = 0; i < bid.batch; ++i) {
            bid.player[bid.plen][i] = tmp[i];
        }
        ++bid.plen;
        return;  
    }
    if (d == bid.num_player) return;
    tmp[len] = d + 1;
    com(d + 1, len + 1);
    com(d + 1, len);
}

void buidHostCommunication() {
	umask(0);
	for (int i = 0; i <= bid.num_host; ++i) {
		if (i == 0) {
			sprintf(FIFO[i], "/tmp/Host.FIFO");
			if (mkfifo(FIFO[i], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1
	            && errno != EEXIST)
	        	errExit("mkfifo");
		}
		else {
			sprintf(FIFO[i], "/tmp/Host%d.FIFO", i);
			if (mkfifo(FIFO[i], S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) == -1
	            && errno != EEXIST)
	        	errExit("mkfifo");
		}
	}
}

void init(int num_host, int num_player) {
	bid.plen = 0;
	bid.batch = MAXN;
	bid.num_host = num_host;
	bid.num_player = num_player;
	memset(bid.player, 0, sizeof(bid.player));
	com(0, 0);

	for (int i = 0; i < bid.batch; ++i)
		idx[i] = i;
	for (int i = 1; i <= num_host; ++i) {
		random_key[i] = rand() % MAXRAND;
		hosts[random_key[i]] = i;
	}
	memset(host.results, 0, sizeof(host.results));
	buidHostCommunication();
}

void execHost(int host_id, int random_key, int depth) {
	sprintf(arg1, "%d", host_id);
	sprintf(arg2, "%d", random_key);
	sprintf(arg3, "%d", depth);
	char *args[] = {"./host", arg1, arg2, arg3, NULL};
	execve("host", args, NULL);
}

void assignPlayers(FILE* fpr, int num_comp) {
	fprintf(fpr, "%d", bid.player[num_comp][0]);
	for (int i = 1; i < bid.batch; ++i) {
		fprintf(fpr, " %d", bid.player[num_comp][i]);
	}
	fprintf(fpr, "\n");
    fflush(fpr);
    fclose(fpr);
}

int handle_read(FILE *fpr) {
	fscanf(fpr, "%d", &host.random_key);
	for (int i = 0; i < bid.batch; ++i) {
		fscanf(fpr, "%d %d", &_, &host.results[i]);
		scores[i] += (bid.batch - host.results[i]);
	}
	return host.random_key;
}

void sendStopmessage() {
	for (int i = 1; i <= bid.num_host; ++i) {
		if ((fp = fopen(FIFO[i], "w")) == NULL)
			errExit("fopen");
		fprintf(fp, "-1 -1 -1 -1 -1 -1 -1 -1\n");
		fflush(fp);
	}
}

int cmp(const void *a, const void *b) {
	return scores[*(int *)b] - scores[*(int *)a];
}

void outputRanks() {
	qsort(idx, bid.batch, sizeof(int), cmp);
	tmp[idx[0]] = 1;
	for (int i = 1; i < bid.batch;) {
		while (i < bid.batch && scores[idx[i]] == scores[idx[i - 1]]) {
			tmp[idx[i]] = tmp[idx[i - 1]];
			++i;
		}
		if (i < bid.batch) {
			tmp[idx[i]] = tmp[idx[i - 1]] + 1;
			++i;
		}
	}
	for (int i = 0; i < bid.batch; ++i) {
		printf("%d %d\n", i + 1, tmp[i]);
	}
}

void run() {
	int child_pid, wpid;
	int num_comp = 0;
	int read_cnt = 0;
	int tot_comp = bid.plen;

	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) errExit("signal");

	for (int i = 1; i <= bid.num_host && num_comp < tot_comp; ++i) {
		if ((child_pid = fork()) < 0) {
			errExit("fork");
		}
		else if (child_pid == 0) {
			execHost(i, random_key[i], 0);
		}
		else {
			if ((fp = fopen(FIFO[i], "w")) == NULL)
				errExit("fopen");
			assignPlayers(fp, num_comp);
			++num_comp;
		}
	}
	/*
	fp[0] = fopen(FIFO[0], "r");
	dummy = open(FIFO[0], O_WRONLY);

	while (num_comp < tot_comp) {
		key = handle_read(fp[0]);
		++read_cnt;

		if ((child_pid = fork()) < 0) {
			errExit("fork");
		}
		else if (child_pid == 0) {
			execHost(hosts[key], key, 0);
		}
		else {
			assignPlayers(fp[hosts[key]], num_comp);
			++num_comp;
		}
	}

	while (read_cnt < tot_comp) {
		handle_read(fp[0]);
		++read_cnt;
	}
	sendStopmessage();
	while ((wpid = wait(NULL)) > 0);
	outputRanks();
	*/
	while ((wpid = wait(NULL)) > 0);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage:./bidding_system [host_num] [player_num]\n");
		exit(0);
	}

	int num_host = (int)strtol(argv[1], NULL, 10);
	int num_player = (int)strtol(argv[2], NULL, 10);
	init(num_host, num_player);
	run();
	exit(0);
}