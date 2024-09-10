#ifndef generic_functions
#define generic_functions

// Set buffer size for reading files/programs output (It must be greater than the size of the string read using "fgets()")
#define BUFFER_SIZE 50

// Set buffer size for command line instruction to execute (the prompt)
#define TERMINAL_BUFFER_SIZE 300

// Set string array default quantity of elements
#define ARRAY_MAX_ELEMENTS 100
// Set string array element size
#define STRING_BUFFER_SIZE 20

void clear_input_buffer();
    /*
    This function clears the input buffer calling many times getchar()
    */

void clean_input_string(char *input_string, int char_to_replace);
    /*
    This function replaces the desired character on the string, by a null character '\0'.
    This function is practical to replace the default end-of-line character '/n' written by default when fgets() is used.

    -------
    Input:
        char *input_string
            The input string which contains an end-of-line character to modify.
        int char_to_replace
            An integer containing the number of the character in the ASCII table to replace/remove by '\0'.

    -------
    Output:
        char *input_string
            A modification of the value of the input argument "char *input_string".
    */

void clear_string(char *target_string);
    /*
    This functions clears the content of a string setting the NULL character to the first element of the array
    (The computer will therefore understand that the variable has available storage).

    This function will not overwrite the content of the string.

    ------
    Input:
        char *target_string
            A string whose content will be discarded

    ------
    Output:
        char *target_string
            A modification of the value of the input argument "char *target_string".
    */

int read_input_database(char output_string_array[][STRING_BUFFER_SIZE], char *database_path);
    /*
    This function opens, reads and stores in memory the content of the loaded text file. Information line by line is saved as an element of an array.

    ------
    Input:
        char output_string_array[][STRING_BUFFER_SIZE]
            An array of strings where the content of the file will be saved
            macro STRING_BUFFER_SIZE
                Preprocessor directive containing a constant to specify the size of each string in the array.
        char *database_path
            A string containing the path of the file to open


    ------
    Output:
        char output_string_array[][STRING_BUFFER_SIZE]
            A modification of the value of the input argument "char output_string_array[][STRING_BUFFER_SIZE]".
    */

int obtain_quantity_of_elements(char string_array[][STRING_BUFFER_SIZE], int array_size);
     /*
    This function counts the number of non-null elements of a string_array (list of strings).
    This function expects that after finding the first null element, the remaining content of the variable contains null elements (reserved memory slots for the variable)

    ------
    Input:
        char string_array[][STRING_BUFFER_SIZE]
            A two dimensional char array meant to contain a list of strings.
            macro STRING_BUFFER_SIZE
                Preprocessor directive containing a constant to specify the size of each string in the array.
        int array_size
            A int containing the maximum quantity of elements of "string_array[][STRING_BUFFER_SIZE]" (it does not contain the size in bytes).

    --------
    Ouput:
        int i
            An index containing the last position where the array had a non-null string (i.e, the number of non-null/non-empty elements in the array).
    */

void build_up_program_command(char *terminal_output_command, char *program_call, int args_number, ...);
    /*
    This function concatenates a string containing a program call with its args for executing the expression in the terminal.

    NOTE: If the user submits a number for the parameter "int args_number" that is greater than the number of additional args for this function,
    the program execution will have an unexpected behavior and therefore, it will crash.

    ------
    Input:
        char *terminal_output_command
            A disposable string meant to store the whole program call (with input args).
        char *program_call
            A string containing the program call without its parameters.
        int args_number
            An integer specifying with exacitude the number of args that will be appended to the "*program_call" string
            (Arguments are delimited by this function with spaces).
        char * ... (Multiple)
            Many strings are expected, the quantity is specified by the previous parameter.

    ------
    Output:
        char *terminal_output_command
            A modification of the value of the input argument "char *terminal_output_command".
    */

int read_program_output(char *string_to_write, char *terminal_command);
    /*
    This function reads the output of the program executed by the instruction "terminal_command" and stores its output in the chosen string.
    The ouput of the program executed will be separated with semicolon for each line of text.

    ------
    Input:
        char *string_to_write
            A string whose content will store the output from "FILE *program_execution".
        char *terminal_command
            A string containing the instruction to execute a program in the terminal, whose ouput will be stored in "char *string_to_write".

    ------
    Output:
        char *string_to_write
            A modification of the value of the input argument "char *string_to_write".
    */


#endif