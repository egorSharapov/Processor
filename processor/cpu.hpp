#ifndef CPU_HPP_INCLUDED
#define CPU_HPP_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "C:\Users\Egor\projects\processor\enum_args.hpp"
#include "C:\Users\Egor\projects\processor\cpu\stack\stack.hpp"


typedef struct
{
    Stack_t *stack = NULL;
    Stack_t *call_stack = NULL;
    char    *code  = NULL;
    int     Regs[sizeof (Regs_number)] = {10, 10, 10, 10};
    int     Ram[100];
} cpu;

const int version = 2;

char *open_n_read (const char * file_name, unsigned long *size);
void cpu_dump (FILE *dump_file, Stack_t *stack, char *code, int ip);
int get_arg (cpu *my_cpu, char cmd, int *ip);
int set_arg (cpu *my_cpu, char cmd, int *ip);
FILE *open_file (const char *file_name, const char *mode);
int soft_cpu (cpu *my_cpu, FILE *dump_file = stdout);

extern FILE *output_file;

#endif