#include "assembler.hpp"

const char *file_name = "assembler_input.txt";
const char *output_file_name = "C:\\Users\\Egor\\projects\\processor\\assembler.out";

int main ()
{

    Text source_buf = {};
    
    count_and_read (file_name, &source_buf);
    create_pointers (&source_buf);

    write_to_output_file (&source_buf, output_file_name);

    return 0;
}