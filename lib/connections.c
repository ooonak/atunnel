#include "connections.h"

#include <fcntl.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Adapted from https://www.man7.org/linux/man-pages/man3/getaddrinfo.3.html

#define BACKLOG 16

int init_server(char *port)
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int sfd, s;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;     /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* TCP */
    hints.ai_flags = AI_PASSIVE;     /* For wildcard IP address */
    hints.ai_protocol = 0;	     /* Any protocol */
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    s = getaddrinfo(NULL, port, &hints, &result);
    if (s != 0) {
	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
	return -1;
    }

    /* getaddrinfo() returns a list of address structures.
       Try each address until we successfully bind(2).
       If socket(2) (or bind(2)) fails, we (close the socket
       and) try the next address. */

    for (rp = result; rp != NULL; rp = rp->ai_next) {
	sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
	if (sfd == -1)
	    continue;

	if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
	    break; /* Success */

	close(sfd);
    }

    freeaddrinfo(result); /* No longer needed */

    if (rp == NULL) { /* No address succeeded */
	fprintf(stderr, "Could not bind\n");
	return -1;
    }

    s = set_non_blocking(sfd);
    if (s != 0) {
	close(sfd);
	return -1;
    }

    s = listen(sfd, BACKLOG);
    if (s != 0) {
	perror("listen");
	close(sfd);
	return -1;
    }

    printf("Listening for TCP connections on port %s socket fd %d.\n", port,
	   sfd);

    return sfd;
}

int set_non_blocking(int sfd)
{
    int flags, s;

    flags = fcntl(sfd, F_GETFL, 0);
    if (flags == -1) {
	perror("fcntl");
	return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl(sfd, F_SETFL, flags);
    if (s == -1) {
	perror("fcntl");
	return -1;
    }

    return 0;
}
