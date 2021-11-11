#include <stdint.h>

#define BF_EXIT_SUCCESS 0
#define BF_TAPE_OVERFLOW -3
#define BF_TAPE_UNDERFLOW -4
#define BF_PROGRAM_INVALID_INSTRUCTION -5
#define BF_PROGRAM_LOOP_STOPPED_UNEXPECTED -6

// bf_execute executes the given brainfuck program (zero-terminated string)
// on the given tape (starting at position 0) of length tape_length
// it returns an exit code of 0 on success
extern int bf_execute(const char *program, uint8_t *tape, uint32_t tape_length);
