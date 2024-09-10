#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "generic_functions.h"
#include "set_up_VBS_script.h"


void deinitialize_struct_input_args(input_args *struct_input_args)
{
    /*
    This function is specific and a complement to the creation of a struct "input_args" instance.

    This function deinitializes a "input_args" struct for freeing its memory. It frees the memory and sets to null the address of
    each of its pointers elements and also the very same.
    ------
    Input:
        input_args *struct_input_args
            A struct created belonging to the struct "input_args"

    */
    free(struct_input_args->path_database_file);
    struct_input_args->path_database_file = NULL;

    free(struct_input_args->program_call);
    struct_input_args->program_call = NULL;

    free(struct_input_args->script_args);
    struct_input_args->script_args = NULL;

    free(struct_input_args->path_file_to_write);
    struct_input_args->path_file_to_write = NULL;

    free(struct_input_args);
    struct_input_args = NULL;
}

int read_input_args(int argc, char *argv[], input_args *input_data)
{
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

   bool input_arg_flag = False, script_arg_flag = False, args_arg_flag = False, output_arg_flag = False;

   if (argc > 1)
   {
    for (int i = 1; i < argc; i+=2) // To count only odd positions of the program's execution.
    {
        if (input_arg_flag == False && (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--input")))
        {
            // Parsing string related to input file to read
            input_data->path_database_file = (char*) malloc(sizeof(char) * (strlen(argv[i + 1]) + 1));
            clear_string(input_data->path_database_file); // Clears chunk of memory (Initialization)
            if (input_data->path_database_file == NULL)
            {
                printf("Cannot allocate memory, an error happenned");
                exit(1);
            }
            strcpy(input_data->path_database_file, argv[i + 1]);
            input_arg_flag = True;
        }
        else if (script_arg_flag == False && (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--script")))
        {
            // Parsing string containing the path of the VBS script to execute.
            input_data->program_call = (char*) malloc(sizeof(char) * (strlen(argv[i + 1]) + 1) + strlen("cscript.exe /nologo "));
            clear_string(input_data->program_call); // Clears chunk of memory (Initialization)
            if (input_data->program_call == NULL)
            {
                printf("Cannot allocate memory, an error happenned");
                exit(1);
            }
            // The two instructions below will create the main terminal instruction for executing the VBS script.
            strcat(input_data->program_call, "cscript.exe /nologo "); // Mandatory for correct program execution
            strcat(input_data->program_call, argv[i + 1]);
            script_arg_flag = True;
            printf( "%s go\n", input_data->program_call);
        }
        else if (args_arg_flag == False && (!strcmp(argv[i], "-a") || !strcmp(argv[i], "--args")))
        {
            // Parsing string containing the input args to submit to the VBS script execution command.
            input_data->script_args = (char*) malloc( sizeof(char) * (strlen(argv[i + 1]) + 1));
            clear_string(input_data->script_args); // Clears chunk of memory (Initialization)
            if (input_data->script_args == NULL)
            {
                printf("Cannot allocate memory, an error happenned");
                exit(1);
            }
            strcpy(input_data->script_args, argv[i + 1]);
            args_arg_flag = True;
        }
        else if (output_arg_flag == False && (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")))
        {
            // Parsing string containing the path of the output file. 
            input_data->path_file_to_write = (char*) malloc( sizeof(char) * (strlen(argv[i + 1]) + 1));
            clear_string(input_data->path_file_to_write); // Clears chunk of memory (Initialization)
            if (input_data->path_file_to_write == NULL)
            {
                printf("Cannot allocate memory, an error happenned");
                exit(1);
            }
            strcpy(input_data->path_file_to_write, argv[i + 1]);
            output_arg_flag = True;
        }
        else if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            // Parsing instruction for displaying the following help message
            printf("To execute this program, the following arguments are required:\n\n");
            printf(
            "    -h or --help\n"
            "       Displays a help message with all the input parameters expected for running the program\n"
            "   -i or --input\n"
            "       The path of the input file to read (the one that contains the database, the information to enter into the VBS program).\n"
            "       Use double or single quotes if the path contains whitespaces.\n"
            "   -s or --script\n"
            "       The path of the VBS (Visual Basic Script) program to execute for automating SAP interface.\n"
            "       Use double or single quotes if the path contains whitespaces.\n"
            "   -a or --args\n"
            "       A string listing the expected arguments by the VBS program separated by commas (Expected syntax: \"/arg_n:,/arg_m:,...\").\n"
            "   -o or --output\n"
            "       The path of the output file to create or modify (the one where all the data extracted via SAP will be stored).\n"
            "       Use double or single quotes if the path contains whitespaces.\n\n"
            "Program execution line example:\n"
            "   program.exe -i \"input_file_path\" -s \"script_path\" -o \"output_file_path\" -a arg1,arg,2,...\n"
            );
            return 0;
        }
        else
        {
            printf("Invalid input args.  Use -h / --help command to know the expected input arguments and syntax.");
            return 1;
        }
    }
   }
   else
   {
    printf("Missing expected input arguments. Use -h / --help command to know the expected input arguments and syntax.");
    return 1;
   }

   return 0;
}

void set_VBS_args_string(char *output_str_arg, char *label_input_arg, char *value_input_arg)
{
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
   
    // Copying a value into the string, helps to overwrite its old content
    strcpy(output_str_arg, label_input_arg);
    strcat(output_str_arg, value_input_arg);
}