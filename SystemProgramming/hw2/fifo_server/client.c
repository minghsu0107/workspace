/* fifo_seqnum_client.c
+
+   A simple client that uses a well-known FIFO to request a (trivial)
+   "sequence number service". This client creates its own FIFO (using a
+   convention agreed upon by client and server) which is used to receive a reply
+   from the server. The client then sends a request to the server consisting of
+   its PID and the length of the sequence it wishes to be allocated. The client
+   then reads the server's response and displays it on stdout.
+
+   See fifo_seqnum.h for the format of request and response messages.
+
+   The server is in fifo_seqnum_server.c.
*/
#include "fifo_seqnum.h"

static char clientFifo[CLIENT_FIFO_NAME_LEN];

/* Invoked on exit to delete client FIFO */
static void removeFifo() {
    unlink(clientFifo);
}

int main(int argc, char *argv[]) {
    int serverFd, clientFd;
    struct request req;
    struct response resp;

    if (argc > 1 && strcmp(argv[1], "--help") == 0)
        fprintf(stderr, "%s [seq-len]\n", argv[0]);

    /* Create our FIFO (before sending request, to avoid a race) */

    umask(0);                   /* So we get the permissions we want */
    snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE,
            (long) getpid());
    if (mkfifo(clientFifo, S_IRUSR | S_IWUSR | S_IWGRP) == -1
        && errno != EEXIST)
        errExit("mkfifo");

    if (atexit(removeFifo) != 0)
        errExit("atexit");

    /* Construct request message, open server FIFO, and send message */

    req.pid = getpid();
    int seqlen = 1;
    if (argc > 1)
        seqlen = (int)strtol(argv[1], NULL, 10);
    req.seqLen = seqlen;

    serverFd = open(SERVER_FIFO, O_WRONLY);
    if (serverFd == -1)
        errExit("open");

    if (write(serverFd, &req, sizeof(struct request)) !=
        sizeof(struct request))
        fprintf(stderr, "Can't write to server");

    /* Open our FIFO, read and display response */

    clientFd = open(clientFifo, O_RDONLY);
    if (clientFd == -1)
        errExit("open");

    if (read(clientFd, &resp, sizeof(struct response))
        != sizeof(struct response))
        fprintf(stderr, "Can't read response from server");

    printf("%d\n", resp.seqNum);
    exit(EXIT_SUCCESS);
}