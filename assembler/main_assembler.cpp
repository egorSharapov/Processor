#include "assembler.hpp"
#include "file_analyze.hpp"
#include <malloc.h>

const char *file_path        = "C:\\Users\\Egor\\projects\\processor\\programs\\"; 
const char *output_file_name = "C:\\Users\\Egor\\projects\\processor\\assembler.out";

int main (int argc, const char *argv[])
{
    printf ("initialize...\n");
    Text source = {};

    char *file_dir = create_dir_name (file_path, argv[argc - 1]);

    count_and_read (file_dir, &source);
    
    create_pointers (&source);
    printf ("create pointers succesn\n");
    
    Mark *marks = mark_source (&source);
    
    assemble (&source, marks, output_file_name);
    
    pretty_listing (&source, marks);

    FREE();

    return 0;
}