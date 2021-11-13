#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bf/bf.h"
#include "file/reader.h"
#include "cmdline/options.h"

int main(int argc, char *const argv[])
{
    int help_flag = 0;
    char *file_name = NULL;
    unsigned long tape_size = DEFAULT_TAPE_SIZE;

    if (parse_options(argc, argv, &help_flag, &file_name, &tape_size))
    {
        return EXIT_FAILURE;
    }

    if (help_flag)
    {
        print_usage(argc, argv);
        return EXIT_SUCCESS;
    }

    // This should actually never happen after parse_options is successful (with help_flag==0)
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
        free(program_text);

        printf("Cannot allocate memory for tape, exiting\n");
        return EXIT_FAILURE;
    }

    // Finally, execute the bf program
    int bf_exit = bf_execute(program_text, tape, tape_size);

    free(tape);
    free(program_text);

    if (bf_exit != BF_EXIT_SUCCESS)
    {
        printf("Error: %s (error code %d)\n", bf_execute_error_message(bf_exit), bf_exit);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
