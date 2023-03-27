#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "atunnel.h"

int main(int argc, char* argv[])
{
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

    uint16_t port = (uint16_t)tmp;

    test();

    return EXIT_SUCCESS;
}
