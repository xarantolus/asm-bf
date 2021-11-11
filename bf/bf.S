.intel_syntax noprefix
.global bf_execute
.text

// extern int bf_execute(const char *program, uint8_t *band, uint32_t band_length)
bf_execute:
    // program pointer: rdi
    // band pointer: rsi
    // band length: edx
    // return register: rax
    mov rax, 0
    ret
