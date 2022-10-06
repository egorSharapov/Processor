#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "C:\Users\Egor\projects\processor\enum_args.h"

#define IS_OK(func) if (func == 0)                                                       \
                    {                                                                    \
                        printf ("incorrect input file, error in func: %s\n", #func);     \
                        exit (0);                                                        \   
                    };

enum ERRORS_CODE 
{
    FALL            = 0, // abnormal program termination
    SUCCESS         = 1, // succes
    ERROR           = 2, // typical error
    INPUT_ERROR     = 3, // incorrect comand line input
    OPEN_FILE_ERROR = 4, // file cannot open
    NO_MEM_ERROR    = 5, // no mem for calloc 
};


typedef struct
{
    char *string_point  = NULL; // pointer to a start of string
    int string_len      = 0;    // len of string
} Line;


typedef struct
{
    char * source        = NULL; // pointers massive
    int count_of_symbols = 0;    // count of symbols in source file
    int count_of_strings = 0;    // count of strings in source file
    Line * command_args    = NULL;
    int *buffer = NULL;
} Text;


void create_pointers (Text * text);

ERRORS_CODE count_and_read (const char *file_name, Text * text);
void write_to_output_file (Text *text, const char* output_file_name);
FILE *open_file (const char* output_file_name);
void counting_strings (Text * text);

#endif