#include "bf.h"

char *bf_execute_error_message(int error_code)
{
    switch (error_code)
    {
    case BF_EXIT_SUCCESS:
        return "Success";
    case BF_TAPE_OVERFLOW:
        return "Tape overflow.\nThe program tried to move beyond the tape size provided.";
    case BF_TAPE_UNDERFLOW:
        return "Tape underflow.\nThe program tried to move before the start of the tape.";
    case BF_PROGRAM_LOOP_NO_CLOSING_BRACKET:
        return "No closing bracket in loop.\nThe program wants to skip over a loop, but that loop doesn't end.\nTry adding a matching ']'.";
    case BF_PROGRAM_LOOP_NO_OPENING_BRACKET:
        return "No opening bracket in loop.\nThe program wanted to return to a previous program point, but reached the start of the program instead.\nTry adding a matching '['.";
    default:
        return "Unknown error code";
    }
}
