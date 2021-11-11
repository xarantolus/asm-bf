#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <getopt.h>

#include "bf/bf.h"
#include "file/reader.h"

int parse_options(int argc, char *const argv[], int *flag_help_ptr, char **file_name_ptr, unsigned long *tape_size_ptr)
{
    struct option long_options[] = {
        {"help", no_argument, NULL, 'h'},
        {"tape-size", required_argument, NULL, 's'},
        // According to docs: "Terminate the array with an element containing all zeros."
        // https://www.gnu.org/software/libc/manual/html_node/Getopt-Long-Options.html
        {0, 0, 0, 0},
    };

    while (1)
    {
        // Options with a ":" after them require an additional parameter, e.g.
        // for -f we require a text that defines the function
        int opt = getopt_long(argc, argv, "hs:", long_options, 0);
        if (opt == -1)
        {
            break;
        }

        switch (opt)
        {
        case 0:
        {
            break;
        }
        case 'h':
        {
            *flag_help_ptr = 1;
            break;
        }
        case 's':
        {
            // Parse tape size input
            char *endptr;

            errno = 0;

            unsigned long tape_size = strtoul(optarg, &endptr, 10);
            if (errno != 0)
            {
                printf("parsing command line argument -s/--tape-size: %s\n", strerror(errno));
                return -1;
            }

            if (*endptr != 0)
            {
                printf("parsing command line argument -s/--tape-size: %s is not a valid number\n", optarg);
                return -1;
            }

            *tape_size_ptr = tape_size;
            break;
        }
        case '?':
        {
            // Invalid input, getopt will already have printed an error message
            return -1;
        }
        }
    }

    if (optind + 1 != argc)
    {
        printf("Need exactly one positional file name argument, but got %d\n", argc - optind);
        return -1;
    }

    // set file name pointer to file name
    *file_name_ptr = argv[optind];

    return 0;
}

int main(int argc, char *const argv[])
{
    int help_flag = 0;
    char *file_name = NULL;
    unsigned long tape_size = 250;

    if (parse_options(argc, argv, &help_flag, &file_name, &tape_size))
    {
        return EXIT_FAILURE;
    }

    if (help_flag)
    {
        // TODO: Display help
        printf("Help!\n");
        return EXIT_SUCCESS;
    }

    // This should actually never happen after parse_options is successful
    if (file_name == NULL)
    {
        printf("Error: No file name given\n");
        return EXIT_FAILURE;
    }

    // Make sure our tape size is positive
    if (tape_size <= 0)
    {
        printf("Error: Tape size must be positive\n");
        return EXIT_FAILURE;
    }

    // This is where we will read the program text into
    char *program_text;

    int read_success = read_bf_program(file_name, &program_text);
    if (read_success != ERR_SUCCESS)
    {
        printf("Error while reading file: %s\n", read_bf_program_error_message(read_success));
        return EXIT_FAILURE;
    }

    if (*program_text == 0)
    {
        printf("Error: program text is empty\n");
        return EXIT_FAILURE;
    }

    // Allocate enough memory for the tape
    uint8_t *tape = calloc(tape_size, sizeof(uint8_t));
    if (tape == NULL)
    {
        printf("Cannot allocate memory for tape, exiting\n");
        return EXIT_FAILURE;
    }

    // Finally, execute the bf program
    int bf_exit = bf_execute(program_text, tape, tape_size);

    if (bf_exit != BF_EXIT_SUCCESS)
    {
        printf("Error: %s (%d)\n", bf_execute_error_message(bf_exit), bf_exit);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
