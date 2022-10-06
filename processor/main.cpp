#include "C:\Users\Egor\projects\processor\cpu\stack\check_stack.hpp"
#include "cpu.hpp"

const char *input_file_name = "C:\\Users\\Egor\\projects\\processor\\assembler.out";

int main ()
{
    
    Stack_t stk1 = {};
    stack_ctor (stk1, 1);

    unsigned long size = 0;
    
    int *commands_array = open_n_read (input_file_name, &size);
    
    soft_cpu (&stk1, commands_array, size);

    
    return 0;
}