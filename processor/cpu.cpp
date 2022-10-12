#include <sys\stat.h>
#include <ctype.h>
#include <assert.h>
#include "cpu.hpp"
#include "C:\Users\Egor\projects\processor\cpu\stack\check_stack.hpp"
#include <malloc.h>
#include <math.h>
//--------------------------------------------------------------------------------------------------------------------

FILE *open_file (const char *file_name, const char *mode)
{
    FILE *file = fopen (file_name, mode);
    
    if (file == NULL)
        printf ("open file error at %s\n", file_name);

    return file;
}

//--------------------------------------------------------------------------------------------------------------------

static unsigned long file_size_count (const char * file_name)
{
    assert (file_name);

    struct stat buff = {};
    buff.st_size = 0;

    stat(file_name, &buff);

    return buff.st_size;
}

//--------------------------------------------------------------------------------------------------------------------

char * open_n_read (const char * file_name, unsigned long *size)
{
    assert (file_name);
    assert (size);


    FILE *file = open_file (file_name, "rb");

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

//--------------------------------------------------------------------------------------------------------------------

void cpu_dump (FILE *dump_file, Stack_t *stack, char *code, int ip)
{
    size_t lenght = _msize (code);
    
    fprintf (dump_file, "CPU DUMP\n");

    for (unsigned ind = 0; ind < lenght; ind++)
        fprintf (dump_file, "%02d  ", ind);
    
    fprintf (dump_file, "\n");
    
    fprintf (dump_file, "\n");

    for (unsigned ind = 0; ind < lenght; ind++)
    {
        fprintf (dump_file, "%2d  ", code[ind]);
        //fprintf (dump_file, "%2d  ", *(int *) code ())
    }
    
    fprintf (dump_file, "\n");
    
    ip -= 2;
    
    while (ip--)
        fprintf (dump_file, "____");
    
    fprintf (dump_file, "/\\");
    printf ("!");
    stack_dump (dump_file, stack, FULL);
}

//--------------------------------------------------------------------------------------------------------------------

static bool title_ok (char *code)
{
    int ip = 0;

    if (code[ip + 1] != 'P' or code[ip] != 'C')
    {
        printf ("wrong signature: expected CP, but recieved %c%c", code[ip], code[ip + 1]);
        return 0;
    }
    
    if (code[ip + 2] != version)
    {
        printf ("buy new processor, your version is %d", code[ip + 2]);
        return 0;
    }

    return 1;

}

//--------------------------------------------------------------------------------------------------------------------
#define DEF_CMD(cmd_name, cmd_num, arg_type, code) \
        case (CMD_##cmd_name):                     \
        {                                          \
            code                                   \
        }                                          \
        break;                                     \

int soft_cpu (cpu *my_cpu, FILE* dump_file)
{
    int size    = _msize (my_cpu->code);
    int command = 0;
    int ip      = 3;

    if (!title_ok (my_cpu->code))
        return 1;

    // for (int i = 0; i < size; i++)
    //     printf ("%d ", my_cpu->code[i]);
    
    while ((size - ip) > 0)
    {
        command = my_cpu->code[ip++];

        switch (command & MASK)
        {
        #include "C:\Users\Egor\projects\processor\def_cmd.hpp"
        default:
            break;
        }

    }
    return 0;
}

#undef DEF_CMD

int get_arg (cpu *my_cpu, char cmd, int *ip)
{
    int arg = 0;

    if (cmd & ARG_IMMED)
    {
        arg += *(int *) (my_cpu->code + *ip);
        *ip += sizeof (int);
    }
    if (cmd & ARG_REG)
    {
        arg += my_cpu->Regs[my_cpu->code[*ip]];
        *ip += sizeof (char);
    }
    if (cmd & ARG_MEM)
        arg = my_cpu->Ram[arg];
    return arg;
}


int set_arg (cpu *my_cpu, char cmd, int *ip)
{
    int ram_ind = 0;

    if (cmd & ARG_IMMED)
    {
        ram_ind += *(int *) (my_cpu->code + *ip);
        *ip += sizeof (int);
    }
    if (cmd & ARG_REG)
    {
        ram_ind += my_cpu->Regs[my_cpu->code[*ip]];
        *ip += sizeof (char);
    } 

    return ram_ind;
}


