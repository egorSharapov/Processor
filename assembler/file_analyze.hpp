#ifndef FILE_ANALYZE_HPP_INCLUDED
#define FILE_ANALYZE_HPP_INCLUDED

#include <stdio.h>
#include <assert.h>


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
    char *code = NULL;
} Text;


void create_pointers  (Text * text);
void counting_strings (Text * text);
char is_register      (const char *reg);
void set_reg          (char *code, int *ip, const char *reg);
void set_val          (char *code, int *ip, const int val);
bool is_ram           (char *arg_point);
void set_args         (char *arg_point, char *code, int *ip);
char *skip_space      (char *pointer);

ERRORS_CODE count_and_read (const char *file_name, Text * text);


#endif
