#include <sys\stat.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include "file_analyze.hpp"
#include "C:\Users\Egor\projects\processor\enum_args.hpp"

//--------------------------------------------------------------------------------------------------------------------

static long file_size_count (const char * file_name)
{
    assert (file_name != NULL);

    struct stat buff = {};
    buff.st_size = 0;

    stat(file_name, &buff);

    return buff.st_size;
}

//--------------------------------------------------------------------------------------------------------------------

void counting_strings (Text * text)
{
    assert (text != NULL);

    text->source [text->count_of_symbols] = '\0';
    
    char * point = text->source;
    
    while ((point = strchr (point, '\n')) != NULL)
    {
        if (*(point - 1) == 13)
            *(point - 1) = ' ';
        
        *point = '\0';
        point++;
        text->count_of_strings++;
    }
    text->count_of_strings++;

}

//--------------------------------------------------------------------------------------------------------------------

ERRORS_CODE count_and_read (const char *file_name, Text * text)
{
    assert (text       != NULL);
    assert (file_name  != NULL);

    FILE * input_file = fopen (file_name, "rb");

    if (!input_file)
        return FALL;

    long file_size = file_size_count (file_name);
    
    text->source = (char *) calloc (2*(file_size + 2), sizeof (char));

    if (text->source == NULL)
        return NO_MEM_ERROR;
    
    text->count_of_symbols = fread (text->source, sizeof(char), file_size, input_file);

    if (file_size != text->count_of_symbols)
        return ERROR;

    counting_strings (text);

    text->code = (char*) calloc ((text->count_of_strings)*(4*sizeof (char) + sizeof (int)), 1);


    if (text->code == NULL)
    {
        printf ("calloc code error");
        return NO_MEM_ERROR;
    }
    
    if (fclose (input_file) != 0)
    {
        printf ("close file %s error", file_name);
        return ERROR;
    }

    return SUCCESS;
}

//--------------------------------------------------------------------------------------------------------------------

void create_pointers (Text * text)
{
    assert (text);

    text->command_args = (Line *) calloc (text->count_of_strings, sizeof (Line));
    int index_of_string = 0;
    char * point = text->source;
    
    text->command_args [index_of_string].string_point = point;
    while (index_of_string++ < text->count_of_strings)
    {
        point += strlen (point);
        point += 1;
        text->command_args [index_of_string].string_point = point;
        text->command_args [index_of_string - 1].string_len = point - text->command_args [index_of_string - 1].string_point - 2;
    }

}

//--------------------------------------------------------------------------------------------------------------------

char is_register  (const char *reg)
{
    if (strcmp (reg, "ax") == 0)
        return ax;
    
    if (strcmp (reg, "bx") == 0)
        return bx; 

    if (strcmp (reg, "cx") == 0)
        return cx;

    if (strcmp (reg, "dx") == 0)
        return dx;

    return 0;
}


void set_reg (char *code, int *ip, const char *reg)
{
    char reg_number = is_register (reg);

    if (reg_number != 0)
    {
        code[*ip - 1] = code[*ip - 1] | ARG_REG;
        
        code[*ip] = reg_number;
        *ip += 1;
    }
}

void set_val (char *code, int *ip, const int val)
{

    code[*ip - 1] = (code[*ip - 1] | ARG_IMMED);

    *(int*)(code + *ip) = val;
    *ip += sizeof (int);
}


bool is_ram (char *arg_point)
{
    char *begin = strchr (arg_point, '[');
    char *end = strchr (arg_point, ']');
    
    if (begin and end)
    {
        *begin = ' ';
        *end   = ' ';
        return true; 
    }

    return false;
}


void set_args (char *arg_point, char *code, int *ip)
{
    char reg[3] = {};
    int val     = 0;

    if (sscanf (arg_point, "%d+%s", &val, reg) == 2)
    {
        set_val (code, ip, val);
        set_reg (code, ip, reg);
        code[*ip] = CMD_ADD;
        *ip += sizeof (char);
    }
    else if (sscanf (arg_point, "%d", &val) == 1)
        set_val (code, ip, val);   

    else if (sscanf (arg_point, "%s", reg)  == 1)
        set_reg (code, ip, reg);
}

char *skip_space (char *pointer)
{
    while (*pointer == ' ')
        pointer++;
    return pointer;
}

