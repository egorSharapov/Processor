#include "assembler.hpp"
#include <sys\stat.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

//--------------------------------------------------------------------------------------------------

static long file_size_count (const char * file_name)
{
    assert (file_name != NULL);

    struct stat buff = {};
    buff.st_size = 0;

    stat(file_name, &buff);

    return buff.st_size;
}

//--------------------------------------------------------------------------------------------------

void counting_strings (Text * text)
{
    assert (text != NULL);

    text->source [text->count_of_symbols] = '\0';
    
    char * point = text->source;
    
    while ((point = strchr (point, '\n')) != NULL)
    {
        *point++ = '\0';
        text->count_of_strings++;
    }
    text->count_of_strings++;

}

//--------------------------------------------------------------------------------------------------

ERRORS_CODE count_and_read (const char *file_name, Text * text)
{
    assert (text       != NULL);
    assert (file_name  != NULL);

    FILE * input_file = fopen (file_name, "rb");

    if (!input_file)
        return FALL;

    long file_size = file_size_count (file_name);
    
    text->source = (char *) calloc ((file_size + 2), sizeof (char));

    if (text->source == NULL)
        return NO_MEM_ERROR;
    
    text->count_of_symbols = fread (text->source, sizeof(char), file_size, input_file);

    if (file_size != text->count_of_symbols)
        return ERROR;

    counting_strings (text);
    
    text->buffer = (int*) calloc (2*(text->count_of_strings)*sizeof (int), 1);
    
    if (text->buffer == NULL)
    {
        printf ("calloc buffer error");
        return NO_MEM_ERROR;
    }
    
    if (fclose (input_file) != 0)
    {
        printf ("close file %s error", file_name);
        return ERROR;
    }

    return SUCCESS;
}

//--------------------------------------------------------------------------------------------------

void create_pointers (Text * text)
{
    assert (text);

    text->command_args = (Line *) calloc (text->count_of_strings, sizeof (Line));
    printf ("source = %u\n", _msize (text->command_args));
    int index_of_string = 0;
    char * point = text->source;
    
    text->command_args [index_of_string].string_point = point;
    while (index_of_string++ < text->count_of_strings)
    {
        point += strlen (point);
        point++;
        text->command_args [index_of_string].string_point = point;
        text->command_args [index_of_string - 1].string_len = point - text->command_args [index_of_string - 1].string_point - 2;
    }

}

//--------------------------------------------------------------------------------------------------

void write_to_output_file (Text *source_buf, const char* output_file_name)
{
    int line = 0;
    char cmd[5] = {};
    int index = 0;

    while (line < source_buf->count_of_strings)
    {
        sscanf (source_buf->command_args[line].string_point, "%s", cmd);

        if (strcmp (cmd, "CP") == 0)
        {
            int version = -1;
            sscanf (strstr (source_buf->command_args[line].string_point, cmd) + strlen(cmd), "%d", &version);
            printf ("version = %d\n", version);
            source_buf->buffer[index++] = version;
        }
        if (strcmp (cmd, "push") == 0)
        {
            int val = 0;
            
            IS_OK (sscanf (strstr (source_buf->command_args[line].string_point, cmd) + strlen(cmd), "%d", &val))
            
            source_buf->buffer[index++] = PUSH;
            source_buf->buffer[index++] = val;

        }
        if (strcmp (cmd, "in") == 0)
            source_buf->buffer[index++] = IN;

        if (strcmp (cmd, "add") == 0)
            source_buf->buffer[index++] = ADD;

        if (strcmp (cmd, "sub") == 0)
            source_buf->buffer[index++] = SUB;

        if (strcmp (cmd, "mul") == 0)
            source_buf->buffer[index++] = MUL;

        if (strcmp (cmd, "div") == 0)
            source_buf->buffer[index++] = DIV;
        
        if (strcmp (cmd, "out") == 0)
            source_buf->buffer[index++] = OUT;
        
        line++;
    }

    FILE *output_file = open_file (output_file_name);
    printf ("%d\n", _msize (source_buf->buffer));

    printf ("number = %d\n", fwrite (source_buf->buffer, sizeof(int), index, output_file));
    printf ("number = %d\n", index);

    fclose (output_file);
}


FILE *open_file (const char* output_file_name)
{
    FILE *file = fopen (output_file_name, "wb");

    if (file == NULL)
        printf ("open file error");

    return file;

}

