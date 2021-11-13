#include <stdint.h>

#define BF_EXIT_SUCCESS 0
#define BF_TAPE_OVERFLOW -3
#define BF_TAPE_UNDERFLOW -4
#define BF_PROGRAM_LOOP_NO_CLOSING_BRACKET -6
#define BF_PROGRAM_LOOP_NO_OPENING_BRACKET -7

// bf_execute executes the given brainfuck program (zero-terminated string)
// on the given tape (starting at position 0) of length tape_length
// it returns an exit code of 0 on success
extern int bf_execute(const char *program, uint8_t *tape, uint32_t tape_length);

// bf_execute_error_message translates the int returned from bf_execute 
// into a readable representation for users
char *bf_execute_error_message(int error_code);
