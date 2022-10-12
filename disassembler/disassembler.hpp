#ifndef DISASSEMBLER_HPP_INCLUDED
#define DISASSEMBLER_HPP_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include "C:\Users\Egor\projects\processor\enum_args.hpp"

char *open_n_read (const char * file_name, unsigned long *size);
void print_args   (FILE *output_file, int arg_type, char *cmd_array, int *ip);
void disassemble  (char *buff, FILE *output_file, int size);
#endif