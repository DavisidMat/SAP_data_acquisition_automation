#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "generic_functions.h"
#include "set_up_VBS_script.h"

int main(int argc, char *argv[])
{
    // String constants
    FILE *file_to_write = NULL;
    char file_open_mode[] = "a"; // "a" to append, "r+" reading and writing

    // List of variables to reuse
    // Create structs for this data ❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗❗
    char terminal_command[TERMINAL_BUFFER_SIZE];
    char article_id_instance[BUFFER_SIZE];
    char string_to_write[BUFFER_SIZE];
    int end_status = 0;
    
    input_args program_args ;
    int status_input_args = read_input_args(argc, argv, &program_args);
    if (status_input_args == 1)
    {
        return 1;
    }

    char part_id[ARRAY_MAX_ELEMENTS][STRING_BUFFER_SIZE] = {0};
    end_status = read_input_database(part_id, program_args.path_database_file);
    if (end_status == 1)
    {
        printf("Impossible to open the database file");
        return 1;
    }

    //Opening output text file
    file_to_write = fopen(program_args.path_file_to_write, file_open_mode);
    if (file_to_write == NULL)
    {
        printf("Impossible to open the log file");
        return 1;
    }

    int array_size = (sizeof(part_id) / sizeof(part_id[0]));

    int elements_database_array = obtain_quantity_of_elements(part_id, array_size);
    if (elements_database_array == 0)
    {
        printf("The loaded database file is empty");
        return 1;
    }
   
    for (int index = 0; index < elements_database_array; index++)
    {
        // Calling function to write article_id input arg
        set_VBS_args_string(article_id_instance, program_args.script_args, part_id[index]);
        // Writing the final string to execute in the terminal
        build_up_program_command(terminal_command, program_args.program_call, 1, article_id_instance);

        // Command line execution
        printf("Executing the command \"%s\"\n", terminal_command);

        end_status = read_program_output(string_to_write, terminal_command);
        if (end_status == 1)
        {
            printf("There was a problem executing the SAP program");
            return 1;
        }
        else if (string_to_write[0] == '\n') // '\n' is used because it's the character written by default at the end of call of read_program_output().
        {
            printf("The program couldn't be executed in SAP or its output content is empty");
            return 1;
        }
        printf("Value Read: %s\n",string_to_write);
        // Writing program's output in a text file
        fprintf(file_to_write, "%s", string_to_write);
    }
    // Close file to write
    fclose(file_to_write);

    deinitialize_struct_input_args(&program_args);

    return 0;
}


// To compile the code and obtain .exe file
// gcc main.c generic_functions.c set_up_VBS_script.c -o program_demo.exe
// ./program_demo.exe

// ./program_demo.exe -i "../database_for_transactions/pivot_lists.txt" -s "../Scripts_from_SAP_GUI/obtain_part_price_and_quantities.vbs" -o "../SAP_logs/test.txt" -a /article_id:
