#include "C:\Users\Egor\projects\processor\enum_args.h"
#include "disassembler.hpp"

const char *input_file_name = "C:\\Users\\Egor\\projects\\processor\\assembler.out";

int main ()
{
    FILE *output_file = fopen ("disassembler_output.txt", "wb");
    
    unsigned long size = 0;
    int *buff = open_n_read (input_file_name, &size);
    int command = 0;
    int index = 0;
    

    while (size--)
    {
        command = buff[index++];

        switch (command)
        {
        case PUSH: 
        {
            int val = buff[index++];
            fprintf (output_file, "%s %d\n", "push", val);
            break;
        }
        case ADD:
        {
            fprintf (output_file, "%s\n", "add");
            break;
        }
        case DIV:
        {
            fprintf (output_file, "%s\n", "div");
            break;
        }
        case OUT:
        {
            fprintf (output_file, "%s\n", "out");
            break;
        }
        default:
            break;
        }

    }
    return 0;
}