#include <errno.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "options.h"

void print_usage(int argc, char *const argv[])
{
    char *program_name;
    if (argc == 0)
    {
        program_name = "abf";
    }
    else
    {
        program_name = argv[0];
    }

#define USAGE_STRING                                                                             \
    "Usage: %s [OPTION] FILE\n"                                                                  \
    "%s is a brainfuck interpreter written in Assembly.\n\n"                                     \
    "Options:\n"                                                                                 \
    "    -s, --tape-size=NUM    The tape size to use (default: 250)\n"                           \
    "                           Change this if your program overflows the default tape size\n\n" \
    "The FILE argument must point to a file containing a brainfuck program.\n\n"                 \
    "Examples:\n\n"                                                                              \
    "  Execute a program from stdin:\n"                                                          \
    "    $ echo \"+++++++++++++++++++++++++++++++++.\" | %s -\n\n"                               \
    "  Execute a program from a file:\n"                                                         \
    "    $ %s hello_world.bf\n\n"                                                                \
    "  Execute a program from a file with tape size 1000:\n"                                     \
    "    $ %s -s 1000 large_tape.bf\n"

    printf(USAGE_STRING, program_name, program_name, program_name, program_name, program_name);
}

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
            return 0;
        }
        case 's':
        {
            // Parse tape size input
            char *endptr;

            errno = 0;

            unsigned long tape_size = strtoul(optarg, &endptr, 10);
            if (errno != 0)
            {
                printf("Error parsing command line argument -s/--tape-size: %s\n", strerror(errno));
                return -1;
            }

            if (*endptr != 0)
            {
                printf("Error parsing command line argument -s/--tape-size: %s is not a valid number\n", optarg);
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
        printf("Error: Need exactly one positional file name argument, but got %d\n", argc - optind);
        print_usage(argc, argv);
        return -1;
    }

    // set file name pointer to file name
    *file_name_ptr = argv[optind];

    return 0;
}
