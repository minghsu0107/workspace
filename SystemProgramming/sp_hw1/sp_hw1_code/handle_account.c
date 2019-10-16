#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXACCOUNT 20
typedef struct {
	int id;
	int balance;
} Account;

Account *accounts = NULL;

void fetch() {
    FILE *fp = fopen("./account_list", "r");
    int rv, i, ret;
    i = 0;
    for (; i < MAXACCOUNT * 2; ++i) {
    	rv = fread(&ret, sizeof(int), 1, fp);
        if (i & 1)
            accounts[i / 2 + 1].balance = ret;
        else
            accounts[i / 2 + 1].id = ret;
        if (rv != 1)
            break;
    }
    fclose(fp);
}

void update_database(int accounts_fd) {
	FILE *fp = fopen("./account_list", "r");
	fwrite(&accounts[1], sizeof(Account), MAXACCOUNT, fp);
	fclose(fp);
	//write(accounts_fd, &accounts[1], sizeof(Account) * MAXACCOUNT);
}

int main() {
	int accounts_fd;
	accounts = (Account*) malloc(sizeof(Account) * (MAXACCOUNT + 1));
	fetch();
	accounts_fd = openat(AT_FDCWD, "./account_list", O_RDWR);
	for (int i = 1; i <= MAXACCOUNT; ++i) {
		printf("id = %d, balance = %d\n", accounts[i].id, accounts[i].balance);
	}
	
	//accounts[1].balance = 10000;
	//update_database(accounts_fd);
	/*
	fetch();
	printf("Updated data:\n");
	for (int i = 1; i <= MAXACCOUNT; ++i) {
		printf("id = %d, balance = %d\n", accounts[i].id, accounts[i].balance);
	}
	
	close(accounts_fd);
	free(accounts);
	*/
	return 0;
}