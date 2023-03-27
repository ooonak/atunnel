#ifndef ATUNNEL_H
#define ATUNNEL_H

#include <stdint.h>

struct server_context {
    int sfd;
};

/**
 * @brief init
 * @param port
 * @return 0 on success.
 */
int init(struct server_context *ctx, char *port);

/**
 * @brief stop
 * @param ctx
 */
void stop(struct server_context *ctx);

#endif // ATUNNEL_H
