#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "bf/bf.h"

int main(int argc, char const *argv[])
{
    const size_t band_size = 250;
    const char *hello_world = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";

    uint8_t *band = calloc(band_size, sizeof(uint8_t));
    if (band == NULL)
    {
        printf("Cannot allocate memory for band, exiting\n");
        return EXIT_FAILURE;
    }

    int bf_exit = bf_execute(hello_world, band, band_size);

    switch (bf_exit)
    {
    case 0:
        printf("Success\n");
        return EXIT_SUCCESS;
    default:
        break;
    }

    return EXIT_SUCCESS;
}
