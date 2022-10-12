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


char * open_n_read (const char * file_name, unsigned long *size)
{
    assert (file_name);
    assert (size);

    FILE *file = fopen (file_name, "rb");
    
    if (file == NULL)
    {
        printf ("open file error at %s\n", file_name);
        return NULL;
    }
    
    *size = file_size_count (file_name);
    
    char *commands_arr = (char*) calloc (*size, sizeof(char));
    
    if (commands_arr == NULL)
    {
        printf ("calloc error");
        return NULL;
    }

    if (*size != fread (commands_arr, sizeof (char), *size, file))
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


#define DEF_CMD(cmd_name, cmd_num, arg_type, code)                   \
{                                                                    \
    case (CMD_##cmd_name):                                           \
    {                                                                \
        fprintf (output_file, "%s", #cmd_name);                      \
        if (arg_type) print_args (output_file, arg_type, buff, &ip); \
        fprintf (output_file, "\n");                                 \
        break;                                                       \
    }                                                                \
}

void disassemble (char *buff, FILE *output_file, int size)
{
    int command = 0;
    int ip = 0;
    
    fprintf (output_file, "%c%c %d\n", buff[ip], buff[ip + 1], buff[ip + 2]);
    ip += 3;
    while ((size - ip) > 0)
    {
        command = buff[ip++];

        switch (command & MASK)
        {
        #include "C:\Users\Egor\projects\processor\def_cmd.hpp"
        default:
            break;
        }

    }
}

#undef DEF_CMD

static const char * is_reg (int reg) 
{
    if (reg == ax) return "ax";
    if (reg == bx) return "bx";
    if (reg == cx) return "cx";
    if (reg == dx) return "dx";

    return NULL;
}

void print_args (FILE *output_file, int arg_type, char *cmd_array, int *ip)
{
    const char *reg = NULL;
    if (arg_type == 1)
    {
        if ((reg = is_reg(cmd_array[*ip])))
        {
            fprintf (output_file, " %s", reg);
            *ip += sizeof (char);
        }
        else
        {
            fprintf (output_file, " %d", *(int*)(cmd_array + *ip));
            *ip += sizeof (int);
        }
    }
    if (arg_type == 2)
    {
        if ((reg = is_reg(cmd_array[*ip])))
        {
            fprintf (output_file, " %s", reg);
            *ip += sizeof (char);
        }
    }
    if (arg_type == 3)
    {
        fprintf (output_file, " %d", cmd_array[*ip]);
        *ip += sizeof (char);
    }
}

