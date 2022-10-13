#include "assembler.hpp"
#include <sys\stat.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#define BINARY_PATTERN "%*c%c%c %c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

//--------------------------------------------------------------------------------------------------------------------

#define DEF_CMD(cmd_name, cmd_num, arg_type, code)  \
    if (strcmp (cmd, #cmd_name) == 0)         \
    {                                         \
        ip += sizeof (char);                  \
        mark_args (arg_type, arg_point, &ip); \
    }                                                                     

Mark* mark_source (Text *source)
{
    int line = 0;
    int ip   = 3;
    char *arg_point = NULL;
    
    Mark *marks = (Mark *) calloc (source->count_of_strings, sizeof (Mark));

    while (line < source->count_of_strings)
    {
        char *point = strchr (source->command_args[line].string_point, ':');
        char cmd[5] = {};

        if (point)
            marks[line].mark_word = source->command_args[line].string_point;
        else
            sscanf (source->command_args[line].string_point, "%s", cmd);

        marks[line].mark_ip = ip;
        
        printf ("cmd = %s\nip = %d\n\n", source->command_args[line].string_point, marks[line].mark_ip);

        arg_point = strstr (source->command_args[line].string_point, cmd);

            
        #include "C:\Users\Egor\projects\processor\def_cmd.hpp"

        line++;
    }
    printf ("mark succes\n");
    return marks;

}
#undef DEF_CMD

//--------------------------------------------------------------------------------------------------------------------

int set_jmp_point (Mark *marks, const char *jmp_word)
{
    assert (marks);
    for (unsigned index = 0; index < _msize (marks)/sizeof (marks[0]); index++)
    {
        if (marks[index].mark_word != NULL)
        {
            if (strncmp (marks[index].mark_word, jmp_word, strlen (jmp_word) - 1) == 0)
            {
                printf ("found!\n");
                return marks[index].mark_ip;
            }
        }
    }
            
    printf ("not found!\n");
    return (-1);
}

//--------------------------------------------------------------------------------------------------------------------

#define DEF_CMD(cmd_name, cmd_num, args, ...)                             \
    if (strcmp (cmd, #cmd_name) == 0)                                     \
    {                                                                     \
        source_buf->code[ip++] = CMD_##cmd_name;                          \
        if (args) write_args (args, arg_pointer, source_buf, marks, &ip); \
    }                                                                     

void assemble (Text *source_buf, Mark *marks, const char* output_file_name)
{
    int line = 0;
    int ip = 0;
    char *arg_pointer = NULL;

    source_buf->code[ip++] = 'C';
    source_buf->code[ip++] = 'P';
            
    source_buf->code[ip++] = 2;

    while (line < source_buf->count_of_strings)
    {
        
        if (marks[line].mark_word)
        {
            line++;
            continue;
        }
            
        char cmd[5] = {};
        sscanf (source_buf->command_args[line].string_point, "%s", cmd);

        arg_pointer = strstr (source_buf->command_args[line].string_point, cmd) + strlen (cmd);
        arg_pointer = skip_space (arg_pointer);
       
        #include "C:\Users\Egor\projects\processor\def_cmd.hpp"

        line++;
    }
    
    printf ("lexer succes\n");
    FILE *output_file = open_file (output_file_name);
    fwrite (source_buf->code, sizeof (char), ip, output_file);
    printf ("write succes\n");
    fclose (output_file);
}

#undef DEF_CMD

//--------------------------------------------------------------------------------------------------------------------

void write_args (int arg_type, char *arg_pointer, Text *source_buf, Mark *marks, int *ip)                                                      
{                            
    int jmp_point = 0;

    if (arg_type == 1)                                                             
    {                                                                          
        if (is_ram (arg_pointer))
            source_buf->code[*ip - 1] = source_buf->code[*ip - 1] | (char) ARG_MEM;

        set_args (arg_pointer, source_buf->code, ip);
    }
    else if (arg_type == 2)
    {
        char reg[3] = {};

        if (is_ram (arg_pointer))
        {
            source_buf->code[*ip - 1] = source_buf->code[*ip - 1] | (char) ARG_MEM;
            set_args (arg_pointer, source_buf->code, ip);
        }
        else
        {
            IS_OK (sscanf (arg_pointer, "%s", reg))
            
            source_buf->code[*ip - 1] = source_buf->code[*ip - 1] | ARG_REG;
            source_buf->code[*ip] = is_register (reg);
            *ip += 1;
        }
    }
    else if (arg_type == 3)
    {
        if (sscanf (arg_pointer, "%d", &jmp_point) == 1)
            set_val (source_buf->code, ip, marks[jmp_point].mark_ip);
        else
            set_val (source_buf->code, ip, set_jmp_point (marks, arg_pointer));
    }
}

//--------------------------------------------------------------------------------------------------------------------

void mark_args (int arg_type, char *arg_point, int *ip)
{

    if ((arg_type == 1) or (arg_type == 2))
    {
        if (strchr (arg_point, '+'))
        *ip += 2*sizeof (char) + sizeof (int);
            
        else if (strchr (arg_point, 'x'))
            *ip += sizeof (char);     
        else
            *ip += sizeof (int);
    }
    else if (arg_type == 3)
        *ip += sizeof (int);
    
}

//--------------------------------------------------------------------------------------------------------------------

void pretty_listing (Text *strings, Mark *marks)
{
    FILE *listing_file = open_file ("C:\\Users\\Egor\\projects\\processor\\output\\listing.txt");

    fprintf (listing_file, " ip   command         mri  id   args\n");
    for (int index = 0; index < strings->count_of_strings; index++)
    {
        int ip = marks[index].mark_ip;

        char *pointer = strings->command_args[index].string_point;
        int str_len   = strings->command_args[index].string_len;

        fprintf (listing_file, "[%02hX] ", ip);

        fprintf (listing_file, " %s", pointer);

        if ((marks[index].mark_word == NULL) and (str_len != 0))
            fprintf (listing_file, BINARY_PATTERN, 16 - str_len, BYTE_TO_BINARY(strings->code[ip]));

        if ((marks[index + 1].mark_ip - ip) == 7)
        {
            fprintf(listing_file, "  %02d", *(int*) (strings->code + ip + 1));
            fprintf(listing_file, " %02d", strings->code[ip + 1 + sizeof(int)]);
        }
        else if ((marks[index + 1].mark_ip - ip) == 5)
            fprintf(listing_file, "  %02d", *(int*) (strings->code + ip + 1));
        
        else if ((marks[index + 1].mark_ip - ip) == 2)
            fprintf(listing_file, "  %02d", strings->code[ip + 1]);
        

        fprintf(listing_file, "\n");
 
    }
    
    fclose (listing_file);
}

//--------------------------------------------------------------------------------------------------------------------

FILE *open_file (const char* output_file_name)
{
    FILE *file = fopen (output_file_name, "wb");

    if (file == NULL)
        printf ("open file error");

    return file;

}