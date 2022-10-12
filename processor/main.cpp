#include "C:\Users\Egor\projects\processor\cpu\stack\check_stack.hpp"
#include "cpu.hpp"

const char *input_file_name = "C:\\Users\\Egor\\projects\\processor\\assembler.out";
const char *dump_file_name = "dump.txt";
int main ()
{
    cpu my_cpu = {};

    Stack_t stk1 = {};
    stack_ctor (stk1, 1);
    
    Stack_t call_stk = {};
    stack_ctor (call_stk, 1);

    my_cpu.stack = &stk1;
    my_cpu.call_stack = &call_stk;

    unsigned long size = 0;
    
    my_cpu.code = open_n_read (input_file_name, &size);
    
    //FILE *dump_file = open_file (dump_file_name, "wb");
    
    soft_cpu (&my_cpu, output_file);


    
    return 0;
}