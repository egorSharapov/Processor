

#define POP_FUNC stack_pop(my_cpu->stack)


#define PUSH_POP(sign) stack_push(my_cpu->stack,  POP_FUNC sign POP_FUNC);

#define JUMP_COND(sign)                                           \
    if (POP_FUNC sign POP_FUNC)                                   \
        {                                                         \
            JUMP_FUNC                                             \
        }

#define JUMP_FUNC                                \
    int jmp_ip = get_arg (my_cpu, command, &ip); \
    ip = jmp_ip;  

#define CALL_FUNC                                \
    int jmp_ip = get_arg (my_cpu, command, &ip); \
    stack_push (my_cpu->call_stack, ip);         \
    ip = jmp_ip;

#define SQRT_FUNC                            \
    int value = stack_pop (my_cpu->stack);   \
    stack_push (my_cpu->stack, sqrt(value));

#define IN_FUNC                      \
    int val = 0;                     \
    printf ("push value = ");      \
    scanf ("%d", &val);              \
    stack_push (my_cpu->stack, val);

#define PUSH_FUNC                             \
    int arg = get_arg (my_cpu, command, &ip); \
    stack_push (my_cpu->stack, arg);          

#define POP_                                              \
    if (command & ARG_MEM)                                \
    {                                                     \
        int ram_ind = set_arg (my_cpu, command, &ip);     \
        my_cpu->Ram[ram_ind] = stack_pop (my_cpu->stack); \
    }                                                     \
    else                                                  \
    {                                                     \
        int reg = my_cpu->code[ip++];                     \
        my_cpu->Regs[reg] = stack_pop (my_cpu->stack);    \
    }


DEF_CMD(PUSH, 1, 1, PUSH_FUNC)

DEF_CMD(IN, 2, 0, IN_FUNC)

DEF_CMD(ADD, 3, 0, PUSH_POP(+))

DEF_CMD(SUB, 4, 0, PUSH_POP(-))

DEF_CMD(MUL, 5, 0, PUSH_POP(*))

DEF_CMD(DIV, 6, 0, PUSH_POP(/))

DEF_CMD(OUT, 7, 0, print_stack_data (stdout, 0, POP_FUNC);)

DEF_CMD(POP, 8, 2, POP_)

DEF_CMD(HLT, 9, 0, return 0;)

DEF_CMD(JMP, 10, 3, JUMP_FUNC)

DEF_CMD(JE, 11, 3, JUMP_COND(==))

DEF_CMD(JNE, 12, 3, JUMP_COND(!=))

DEF_CMD(JB, 13, 3, JUMP_COND(<))

DEF_CMD(JBE, 14, 3, JUMP_COND(<=))

DEF_CMD(JA, 15, 3, JUMP_COND(>))

DEF_CMD(JAE, 16, 3, JUMP_COND(>=))

DEF_CMD(CALL, 17, 3, CALL_FUNC)

DEF_CMD(RET, 18, 0, ip = stack_pop (my_cpu->call_stack);)

DEF_CMD(SQRT, 19, 0, SQRT_FUNC)
