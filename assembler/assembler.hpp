#ifndef ASSEMBLER_HPP_INCLUDED
#define ASSEMBLER_HPP_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "file_analyze.hpp"
#include "C:\Users\Egor\projects\processor\enum_args.hpp"

#define IS_OK(func) if (func == 0)                                                       \
                    {                                                                    \
                        printf ("incorrect input file, error in func: %s\n", #func);     \
                        exit (0);                                                        \
                    };

#define FREE()                    \
    free (marks);                 \
    free (source.command_args);   \
    free (source.source);         \
    free (source.code);
    
const char version = 2;

typedef struct
{
    int   mark_ip   = 0;
    char *mark_word = NULL;
} Mark;

void assemble       (Text *text, Mark *marks, const char* output_file_name);
void write_args     (int args, char *arg_pointer, Text *source_buf, Mark *marks, int *ip);  
Mark *mark_source   (Text *source);
int  set_jmp_point  (Mark *marks, const char *jmp_word);
void pretty_listing (Text *strings, Mark *marks);
FILE *open_file     (const char* output_file_name);
void mark_args      (int arg_type, char *arg_point, int *ip);

#endif