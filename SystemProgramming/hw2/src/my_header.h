#ifndef TLPI_HDR_H
#define TLPI_HDR_H      /* Prevent accidental double inclusion */

#include <sys/types.h>  /* Type definitions used by many programs */
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                        plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */
#include <stdbool.h>    /* 'bool' type plus 'true' and 'false' constants */

#define MAXGR 3005
#define MAXHOST 15
#define MAXN 15
#define MAXBUF 512
#define MAXRAND 65536
#define NUM_ROUNDS 10
#define errExit(a) { perror(a); exit(1); }

typedef struct {
	int plen;
	int batch;
	int num_host;
	int num_player;
	int player[MAXGR][MAXN];
} BidSystem;

typedef struct {
	int random_key;
	int results[MAXN];
} Host;

/* Unfortunately some UNIX implementations define FALSE and TRUE -
   here we'll undefine them */
#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

typedef enum { FALSE, TRUE } Boolean;
 
#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))
 
/* Some systems don't define 'socklen_t' */
#if defined(__sgi)
typedef int socklen_t;
#endif

#if defined(__sun)
#include <sys/file.h>           /* Has definition of FASYNC */
#endif

#if ! defined(O_ASYNC) && defined(FASYNC)
/* Some systems define FASYNC instead of O_ASYNC */
#define O_ASYNC FASYNC
#endif

#if defined(MAP_ANON) && ! defined(MAP_ANONYMOUS)
/* BSD derivatives usually have MAP_ANON, not MAP_ANONYMOUS */
#define MAP_ANONYMOUS MAP_ANON
#endif

#if ! defined(O_SYNC) && defined(O_FSYNC)
/* Some implementations have O_FSYNC instead of O_SYNC */
#define O_SYNC O_FSYNC
#endif

#if defined(__FreeBSD__)
/* FreeBSD uses these alternate names for fields in the sigval structure */
#define sival_int sigval_int
#define sival_ptr sigval_ptr
#endif
#endif