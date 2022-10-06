#include <sys\stat.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "disassembler.hpp"

static unsigned long file_size_count (const char * file_name)
{
    assert (file_name);

    struct stat buff = {};
    buff.st_size = 0;

    stat(file_name, &buff);

    return buff.st_size;
}


int * open_n_read (const char * file_name, unsigned long *size)
{
    assert (file_name);
    assert (size);

    FILE *file = fopen (file_name, "rb");
    
    if (file == NULL)
    {
        printf ("open file error at %s\n", file_name);
        return NULL;
    }
    
    *size = file_size_count (file_name) / sizeof(int);
    
    int *commands_arr = (int*) calloc (*size, sizeof(int));
    
    if (commands_arr == NULL)
    {
        printf ("calloc error");
        return NULL;
    }

    if (*size != fread (commands_arr, sizeof (int), *size, file))
    {
        printf ("fread error");
        return NULL;
    }

    if (fclose (file))
    {
        printf ("close file error at %s\n", file_name);
        return NULL;
    }
    
    return commands_arr;
}