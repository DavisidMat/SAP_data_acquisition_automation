#ifndef set_up_VBS_script
#define set_up_VBS_script

typedef enum { False, True } bool;

typedef struct input_args input_args;
struct input_args
{
    /*
    This struct will contain all the input arguments from the call of this program.
    After using this struct, the function deinitialize_struct_input_args() may be called for deallocating the memory used.
    */
    char *path_database_file; // The path of the input file to read (the one that contains the inputs for each execution of the VBS script).
    char *program_call; // The path of the VBS (Visual Basic Script) program to execute for automating SAP interface
    char *script_args; // A string listing the expected arguments by the VBS program separated by commas.
    char *path_file_to_write; // The path of the output file to create or modify (the one where all the data extracted via SAP will be stored).
};


void deinitialize_struct_input_args(input_args *struct_input_args);
    /*
    This function is specific and a complement to the creation of a struct "input_args" instance.

    This function deinitializes a "input_args" struct for freeing its memory. It frees the memory and sets to null the address of
    each of its pointers elements and also the very same.
    ------
    Input:
        input_args *struct_input_args
            A struct created belonging to the struct "input_args"

    */

int read_input_args(int argc, char *argv[], input_args *input_data);
    /*
    This function uses the struct "input_args".

    Expected input args:
        -h or --help
            Displays a help message with all the input parameters expected for running the program.
        -i or --input
            The path of the input file to read (the one that contains the database, the information to enter into the VBS program).
            Use double or single quotes if the path contains whitespaces.
        -s or --script
            The path of the VBS (Visual Basic Script) program to execute for automating SAP interface
            Use double or single quotes if the path contains whitespaces.
        -a or --args
            A string listing the expected arguments by the VBS program separated by commas.
        -o or --output
            The path of the output file to create or modify (the one where all the data extracted via SAP will be stored).
            Use double or single quotes if the path contains whitespaces.

    The function deinitialize_struct_input_args() may be called at the end to free the memory used by input_args *input_data.

    ------
    Input:
        int argc
            An integer containing the count of input arguments from the program's execution (the ones entered to the main function).
        char *argv[]
            An array of strings containing each of the arguments from the program's execution (the ones entered to the main function).
        input_args *input_data
            A custom struct that contains variables for all the expected input arguments for the execution of the program. It contains:
                char *path_database_file
                    The path of the input file to read (the one that contains the inputs for each execution of the VBS script).
                char *program_call
                    The path of the VBS (Visual Basic Script) program to execute for automating SAP interface
                char *script_args
                    A string listing the expected arguments by the VBS program separated by commas.
                char *path_file_to_write
                    The path of the output file to create or modify (the one where all the data extracted via SAP will be stored).

    ------
    Output:
        input_args *input_data
            A modified version of the struct containing all the data from the input args submitted at the moment of executing the program
    */

void set_VBS_args_string(char *output_str_arg, char *label_input_arg, char *value_input_arg);
     /*
    Because VBS (Visual basic scripts) require an specific syntax for parsing labelled input args, this function builds up an input arg respecting the expected syntax.
    Syntax expected for input arg in VBS scripts:
    "/'_arg_label_':'_arg_value_'" 

    (This function may be called multiple times whenever it is required to name multiple input args for the execution of a program instance).

    ------
    Input:
        char *output_str_arg
            A string containing the input arg with the correct syntax
            (Ensure that the size of this variable is greater than the sum of the following two input args
            This variable should be an empty string to reuse continuously).
        char *label_input_arg
            A string containing the label of the input arg. It must start with a slash ("/""), end with two points (":") and have no whitespaces.
        char *value_input_arg
            A string containing the value of the input arg.

    ------
    Output:
        char *output_str_arg
            A modification of the value of the input argument "char *output_str_arg"
    */


#endif