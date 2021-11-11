.intel_syntax noprefix
.global bf_execute
.text

// extern int bf_execute(const char *program, uint8_t *band, uint32_t band_length)
// return register: rax
bf_execute:
    // Define & Initialize variables

    // Inputs

    // program pointer: rdi
    #define program_ptr rdi

    // tape pointer: rsi
    #define tape_ptr rsi

    // tape length: edx
    #define tape_length edx

    push r12
    // Save the last index+1 we can access in the tape, 
    // if an address is >= last_tape it is out of range
    #define last_tape r12
    mov last_tape, tape_ptr
    // this assumes that the upper 32 bits of rdx are zeroed
    add last_tape, rdx

    push r13
    // The initial tape pointer points to index 0 of the tape,
    // which means that any pointer below it (<) is out of range
    #define first_tape r13
    mov first_tape, tape_ptr


    // Now custom variables we need


    // Since rbx is callee-saved, we need to push it
    push rbx

    // program_start_ptr is a const char* pointing to the start of the program
    #define program_start_ptr rbx
    mov program_start_ptr, rdi

    // while(true) {
    .Lprogram_loop_start:

    // Fetch the current instruction
    #define current_instruction al
    mov current_instruction, [program_ptr]

    .Lcheck_instruction_null_terminator:
    cmp al, '\0'
    JNE .Lcheck_instruction_increment
        // If we have a null terminator, we end the program by returning 0

        mov rax, 0
        JMP .Lend

    .Lcheck_instruction_increment:
    cmp al, '>'
    JNE .Lcheck_instruction_decrement
        // Increment the current tape pointer
        add tape_ptr, 1

        cmp tape_ptr, last_tape
        JNE .Ltape_ptr_no_overflow

            // If we reach this, we are out of bounds of the tape array
            mov rax, -3 // BF_TAPE_OVERFLOW
            JMP .Lend

        .Ltape_ptr_no_overflow:

        // If everything is fine, we can continue the loop
        JMP .Lprogram_loop_end

    .Lcheck_instruction_decrement:
    cmp al, '<'
    JNE .Lcheck_instruction_add
        // Decrement the current tape pointer
        sub tape_ptr, 1

        // make sure we didn't underflow the initial tape pointer
        cmp tape_ptr, first_tape
        JNE .Ltape_ptr_no_underflow

            // Underflow
            mov rax, -4 // BF_TAPE_UNDERFLOW
            JMP .Lend

        .Ltape_ptr_no_underflow:

        // We did not underflow the tape pointer, continue the loop
        JMP .Lprogram_loop_end

    .Lcheck_instruction_add:
    cmp al, '+'
    JNE .Lcheck_instruction_subtract
        // We want to increment the byte at the current tape pointer
        add [tape_ptr], 1
        JMP .Lprogram_loop_end

    cmp al, '-'
    JNE .Lcheck_instruction_open_loop
        // We want to decrement the byte at the current tape pointer
        sub [tape_ptr], 1
        JMP .Lprogram_loop_end

    .Lcheck_instruction_open_loop:
    cmp al, '['
    JNE .Lcheck_instruction_close_loop
        // This instruction jumps *behind* the next ']' if 
        // the current byte on the tape is 0

        // if the current byte is non-zero, we skip the search
        cmp [tape_ptr], 0
        JNE .Lprogram_loop_end

        // Now we should search the next *matching* bracket ]
        // r11 saves the current brace lvl (which is 1 because we just opened a brace)
        mov r11, 1

        .Lbrace_close_search_loop_start:
        add program_ptr, 1
        mov al, [program_ptr]

        // check for null terminator
        cmp al, '\0'
        JNE .Lbrace_close_loop_check_open
            mov rax, -6 // BF_PROGRAM_LOOP_STOPPED_UNEXPECTED
            JMP .Lend

        .Lbrace_close_loop_check_open:
        cmp al, '['
        JNE .Lbrace_close_loop_check_close
            // the brace lvl goes up
            add r11, 1
            JMP .Lbrace_close_search_loop_cond

        .Lbrace_close_loop_check_close:
        cmp al, ']'
        JNE .Lbrace_close_search_loop_cond
            // the brace lvl goes down
            sub r11, 1
            //JMP .Lbrace_close_search_loop_cond
        
        .Lbrace_close_search_loop_cond:
        // if we aren't on a lvl of 0, we should continue
        cmp r11, 0
        JNE .Lbrace_close_search_loop_start

        // So now we exited the loop.
        // The program pointer now points to a ']'
        // When we end the loop below, we will step behind it

        JMP .Lprogram_loop_end

    .Lcheck_instruction_close_loop:
    cmp al, ']'
    JNE .Linvalid_instruction


        JMP  .Lprogram_loop_end

    .Linvalid_instruction:
        // If we reach this, the current instruction/byte is invalid
        mov rax, -5 // BF_PROGRAM_INVALID_INSTRUCTION
        JMP .Lend

    .Lprogram_loop_end:

    // When we reach this, we increment the program pointer to 
    // advance to the next instruction
    add program_ptr, 1

    JMP .Lprogram_loop_start
    // } // end while(true)



    .Lend:
    // End execution by resetting saved registers
    pop rbx
    pop r13
    pop r12

    ret
