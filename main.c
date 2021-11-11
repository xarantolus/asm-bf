#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "bf/bf.h"

int main(int argc, char const *argv[])
{
    const size_t tape_size = 250;
    const char *hello_world = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";

    uint8_t *tape = calloc(tape_size, sizeof(uint8_t));
    if (tape == NULL)
    {
        printf("Cannot allocate memory for tape, exiting\n");
        return EXIT_FAILURE;
    }

    int bf_exit = bf_execute(hello_world, tape, tape_size);

    if (bf_exit != BF_EXIT_SUCCESS)
    {
        printf("Error: %s (%d)\n", bf_execute_error_message(bf_exit), bf_exit);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
