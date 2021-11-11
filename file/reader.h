#define ERR_SUCCESS 0
#define ERR_OPEN_FILE -1
#define ERR_ALLOCATE_MEMORY -2
#define ERR_FILE_NOT_FULLY_READ -3
#define ERR_FILE_CLOSE_FAIL -4

// read_bf_program reads a program from the file at file_path and writes
// the content to a string of which the address is written to destination.
// It returns 0 on success and a negative value on failure
int read_bf_program(const char *file_path, char **destination);

// read_bf_program_error_message returns an appropriate error message for the error codes returned by read_bf_program
char *read_bf_program_error_message(int exit_code);
