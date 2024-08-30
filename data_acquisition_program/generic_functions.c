#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "generic_functions.h"

void clear_input_buffer()
{
    /*
    This function clears the input buffer calling many times getchar()
    */
   int buffer_char = 0;
   while((buffer_char = getchar()) != '\n' && buffer_char != EOF);
}

void clean_input_string(char *input_string, int char_to_replace)
{
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

    char *char_position = NULL;
    // The following instruction will save in memory the position of the desired character to replace
    char_position = strchr(input_string, char_to_replace);

    if (char_position != NULL) /// Checks if the desired character was found
    {
        // Value swap because the character to replace was found
        *char_position = '\0';
    }
}

void clear_string(char *target_string)
{
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

   target_string[0] = '\0';
}

int read_input_database(char output_string_array[][STRING_BUFFER_SIZE], char *database_path)
{
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

   FILE *file_database = NULL;
   char buffer_string[BUFFER_SIZE] = {0};

   file_database = fopen(database_path, "r");
   if (file_database == NULL)
   {
        printf("Impossible to open database file");
        return 1;
   }
   int index = 0;
   while (feof(file_database) == 0) // Checks if the program has reached end of file
    {
        // Checks if there's a problem or if the program is reading beyond the end of the file
        if (ferror(file_database) != 0)
        {
            printf("Error reading program output\n");
            return 1;
        }
        // An iteration per line of text output from the database file
        if (fgets(buffer_string, BUFFER_SIZE, file_database))
        {
            clean_input_string(buffer_string, ';'); //To delete the separator
            strcpy(output_string_array[index], buffer_string); // To save the content of the string into the array
            index++;
        }
    }
    fclose(file_database);
    return 0;
}

int obtain_quantity_of_elements(char string_array[][STRING_BUFFER_SIZE], int array_size)
{
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
   
   for (int i = 0; i < array_size; i++)
   {  
    if (string_array[i][0] == '\0') // Check if the element of the table is empty
    {
        return i;
    }
   }
}

void build_up_program_command(char *terminal_output_command, char *program_call, int args_number, ...)
{
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

    // Copying the value of the program call string (it also overwrites its old value)
    strcpy(terminal_output_command, program_call);

    if (args_number == 0)
    {
        // No input arguments for executing the program
        return;
    }

    va_list program_args;
    va_start(program_args, args_number);
    for (int i = 0; i < args_number; i++)
    {
        // To add a whitespace to the string
        strcat(terminal_output_command, " ");
        // To append to the string the arg specified
        strcat(terminal_output_command, va_arg(program_args, char *));
    }

    va_end(program_args);

}

int read_program_output(char *string_to_write, char *terminal_command)
{
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
    // Buffer string (the one that stores data in the instance of the loop iteration)

    FILE *program_execution = NULL;
    // Run command line instruction
    program_execution = popen(terminal_command, "r");

    // Validate execution (checks if there are problems trying to run the program)
    if (program_execution == NULL)
    {
        printf("There's a problem executing the terminal command");
        return 1;
    }

    // Creating temporal buffer string
    char output_string[BUFFER_SIZE];
    clear_string(string_to_write);

    // The condition of this while loop, checks if the program has reached the end of the program's execution
    while (feof(program_execution) == 0)
    {
        // An iteration per line of text output from the program
        if (fgets(output_string, BUFFER_SIZE, program_execution))
        {
            //Retouching program output
            clean_input_string(output_string, '\n'); // The last character '\n' is suppressed and replaced by the null character '\0'.
            strcat(output_string, ";");
            strcat(string_to_write, output_string);
        }

        // Checks if there's a problem or if the program is reading beyond the output generated by the terminal execution
        if (ferror(program_execution) != 0)
        {
            printf("Error reading program output\n");
            return 1;
        }
    }
    strcat(string_to_write, "\n");
    // Closing program's execution
    pclose(program_execution);
    return 0;
}