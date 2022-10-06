#include <sys\stat.h>
#include <ctype.h>
#include <assert.h>
#include "cpu.hpp"
#include "check_stack.hpp"
#include <malloc.h>

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

void cpu_dump (FILE *dump_file, Stack_t *stack, int *commands_array, int index)
{
    size_t lenght = _msize (commands_array)/sizeof(commands_array[0]);

    for (unsigned ind = 1; ind < lenght; ind++)
        fprintf (dump_file, "|%2d", ind);
    
    fprintf (dump_file, "|\n");
    
    for (unsigned ind = 1; ind <lenght; ind++)
        fprintf (dump_file, "|==");

    fprintf (dump_file, "|\n");

    for (unsigned ind = 1; ind < lenght; ind++)
        fprintf (dump_file, "|%2d", commands_array[ind]);
    
    fprintf (dump_file, "|\n");
    
    index -= 2;
    
    while (index--)
        fprintf (dump_file, "___");
    
    fprintf (dump_file, "_/\\");
    
    stack_dump (dump_file, stack, FULL);
}

static void chech_title (int *commands_array)
{
    int index = 0;

    if (commands_array[index++] != 'C' or commands_array[index++] != 'P')
        printf ("wrong title");
    
    if (commands_array[index++] != version)
        printf ("buy new processor");

}


int soft_cpu (Stack_t *stack, int *commands_array, unsigned long size, FILE* dump_file)
{
    int command = 0;
    int index   = 0;
    

    chech_title (commands_array);

    
    while (size--)
    {
        command = commands_array[index++];

        switch (command)
        {
        case PUSH: 
        {
            //cpu_dump (dump_file, stack, commands_array, index);
            int val = commands_array[index++];
            stack_push (stack, val);
            break;
        }
        case IN:
        {
            int val = 0;
            printf ("push value = ");
            scanf ("%d", &val);
            stack_push (stack, val);
            break;
        }
        case ADD:
        {
            stack_push (stack, stack_pop (stack) + stack_pop (stack));
            break;
        }
        case MUL:
        {
            //cpu_dump (dump_file, stack, commands_array, index);
            stack_push (stack, stack_pop (stack)*stack_pop (stack));
            break;
        }
        case SUB:
        {
            stack_push (stack, stack_pop (stack) - stack_pop (stack));
            break;
        }
        case DIV:
        {
            stack_push (stack, stack_pop (stack) / stack_pop (stack));
            break;
        }
        case OUT:
        {
            cpu_dump (dump_file, stack, commands_array, index);
            print_stack_data (stdout, 0, stack_pop(stack));
            break;
        }
        default:
            break;
        }

    }
    return 0;
}