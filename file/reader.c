#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <assert.h>

#include "reader.h"

// read_bf_program reads a program from the file at file_path and writes
// the content to a string of which the address is written to destination.
// It returns 0 on success and a negative value on failure
// BUG: This method is not perfect. If the input file contains a null byte, the 
// returned string will also contain that null byte, and other methods will
// assume the string ends there.
int read_bf_program(const char *file_path, char **destination)
{
    FILE *fp;

    // If the file name is '-', we assume the user wants stdin
    if (strcmp(file_path, "-") == 0)
    {
        fp = stdin;
    }
    else
    {
        fp = fopen(file_path, "r");
        if (fp == NULL)
        {
            return ERR_OPEN_FILE;
        }
    }

    // how many bytes to allocate at once
    const size_t buf_step_size = 256;

    char *buf = calloc(buf_step_size, sizeof(char));
    if (buf == NULL)
    {
        return ERR_ALLOCATE_MEMORY;
    }

    size_t buf_offset = 0;

    while (1)
    {
        size_t read_bytes = fread(buf + buf_offset, sizeof(char), buf_step_size, fp);
        if (read_bytes < buf_step_size)
        {
            // null-terminate this string
            buf[buf_offset + read_bytes] = 0;

            break;
        }

        buf_offset += read_bytes;

        char *temp = realloc(buf, buf_offset + buf_step_size);
        if (temp == NULL)
        {
            free(buf);
            return ERR_ALLOCATE_MEMORY;
        }
        buf = temp;
    }

    if (!feof(fp))
    {
        // Return value of fclose is ignored intentionally
        fclose(fp);
        free(buf);

        // Something went wrong while reading
        return ERR_FILE_NOT_FULLY_READ;
    }

    if (fclose(fp))
    {
        free(buf);
        return ERR_FILE_CLOSE_FAIL;
    }

    *destination = buf;
    return ERR_SUCCESS;
}
