#include "atunnel.h"
#include "connections.h"
#include <stdio.h>
#include <unistd.h>

int init(struct server_context *ctx, char *port)
{

    int rv;

    if (ctx == NULL) {
	return -1;
    }

    memset(ctx, 0, sizeof(struct server_context));
    ctx->sfd = -1;

    ctx->sfd = init_server(port);
    if (ctx->sfd == -1) {
	return -1;
    }

    return 0;
}

void stop(struct server_context *ctx)
{
    if (ctx != NULL) {
	if (ctx->sfd != -1) {
	    close(ctx->sfd);
	    ctx->sfd = -1;
	}
    }
}
