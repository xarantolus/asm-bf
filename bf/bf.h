#include <stdint.h>

// bf_execute executes the given brainfuck program (zero-terminated string)
// on the given band (starting at position 0) of length band_length
// it returns an exit code of 0 on success
extern int bf_execute(const char *program, uint8_t *band, uint32_t band_length);
