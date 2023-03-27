#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "atunnel.h"

int main(int argc, char *argv[])
{
    /*
    if (argc != 2)
    {
      printf("atunnel usage: at <port>\n");
      return EXIT_SUCCESS;
    }

    long int tmp = strtol(argv[1], NULL, 10);
    if (tmp <= 0 || tmp > UINT16_MAX)
    {
      printf("atunnel usage: at <port>\n");
      return EXIT_SUCCESS;
    }
    */

    // init(argv[1]);

    struct server_context ctx;
    if (init(&ctx, "8080")) {
	stop(&ctx);
	return EXIT_FAILURE;
    }

    stop(&ctx);
    return EXIT_SUCCESS;
}
