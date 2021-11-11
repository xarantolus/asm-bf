#include "reader.h"

char *read_bf_program_error_message(int error_code)
{
    switch (error_code)
    {
    case ERR_SUCCESS:
        return "Success";
    case ERR_OPEN_FILE:
        return "Opening the file failed";
    case ERR_ALLOCATE_MEMORY:
        return "Could not allocate enough memory for this file";
    case ERR_FILE_NOT_FULLY_READ:
        return "File was not fully read because an error happened while reading.";
    case ERR_FILE_CLOSE_FAIL:
        return "Could not close file after reading.";
    default:
        return "Unknown error code";
    }
}
