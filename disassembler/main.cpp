#include "C:\Users\Egor\projects\processor\enum_args.hpp"
#include "disassembler.hpp"

const char *input_file_name = "C:\\Users\\Egor\\projects\\processor\\assembler.out";



int main ()
{
    unsigned long size = 0;
    
    FILE *output_file = fopen ("disassembler_output.txt", "wb");
    
    char *buff = open_n_read (input_file_name, &size);

    disassemble (buff, output_file, size);

    return 0;
}