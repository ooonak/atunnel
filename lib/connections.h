#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <stdint.h>

/**
 * @brief init_server
 * @param port
 * @return  -1 on error else fd
 */
int init_server(char *port);

/**
 * @brief set_non_blocking
 * @param sfd
 * @return 0 on success
 */
int set_non_blocking(int sfd);

#endif // CONNECTIONS_H
