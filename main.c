#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include "bf/bf.h"
#include "file/reader.h"
#include "cmdline/options.h"
#include "timing/time.h"

int main(int argc, char *const argv[])
{
    int flag_help = 0;
    int flag_verbose = 0;
    char *file_name = NULL;
    unsigned long tape_size = DEFAULT_TAPE_SIZE;

    if (parse_options(argc, argv, &flag_help, &flag_verbose, &file_name, &tape_size))
    {
        return EXIT_FAILURE;
    }

    if (flag_help)
    {
        print_usage(argc, argv);
        return EXIT_SUCCESS;
    }

    // This should actually never happen after parse_options is successful (with flag_help==0)
    if (file_name == NULL)
    {
        printf("Error: No file name given.\n");
        return EXIT_FAILURE;
    }

    // Make sure our tape size is positive
    if (tape_size <= 0)
    {
        printf("Error: Tape size must be positive\n");
        return EXIT_FAILURE;
    }

    if (flag_verbose)
        printf("Reading program from input %s\n", file_name);

    // This is where we will read the program text into
    char *program_text;

    struct timespec read_start = time_now();

    int read_success = read_bf_program(file_name, &program_text);
    struct timespec read_end = time_now();
    if (read_success != ERR_SUCCESS)
    {
        printf("Error while reading file: %s\n", read_bf_program_error_message(read_success));
        return EXIT_FAILURE;
    }

    if (flag_verbose)
        printf("Took %ldns to read input\n", timediff_ns(read_start, read_end));

    if (*program_text == 0)
    {
        printf("Error: program text is empty\n");
        return EXIT_FAILURE;
    }

    // Allocate enough memory for the tape
    uint8_t *tape = calloc(tape_size, sizeof(uint8_t));
    if (tape == NULL)
    {
        free(program_text);

        printf("Cannot allocate memory for tape, exiting\n");
        return EXIT_FAILURE;
    }

    if (flag_verbose)
        printf("Start executing program\n");

    struct timespec execute_start = time_now();

    // Finally, execute the bf program
    int bf_exit = bf_execute(program_text, tape, tape_size);
    struct timespec execute_end = time_now();

    free(tape);
    free(program_text);

    if (flag_verbose)
        printf("Took %ldns to execute the program\n", timediff_ns(execute_start, execute_end));

    if (bf_exit != BF_EXIT_SUCCESS)
    {
        printf("Error: %s (error code %d)\n", bf_execute_error_message(bf_exit), bf_exit);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
