#define DEFAULT_TAPE_SIZE 5000

// print_usage prints the usage of the abf program
void print_usage(int argc, char *const argv[]);

// parse_options parses command-line options from arg & argv
int parse_options(int argc, char *const argv[], int *flag_help_ptr, int *flag_verbose_ptr, char **file_name_ptr, unsigned long *tape_size_ptr);
