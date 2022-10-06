#ifndef CPU_HPP_INCLUDED
#define CPU_HPP_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include "C:\Users\Egor\projects\processor\enum_args.h"
#include "stack.hpp"

int *open_n_read (const char * file_name, unsigned long *size);
void cpu_dump ( Stack_t *stack, int *commands_array, int index);

int soft_cpu (Stack_t *stack, int *commands_array, unsigned long size);


#endif