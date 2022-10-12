#ifndef ENUM_ARGS_HPP_INCLUDED
#define ENUM_ARGS_HPP_INCLUDED


#define DEF_CMD(cmd_name, cmd_num, arg_type, ...) \
    CMD_##cmd_name = cmd_num,                    

enum COMMANDS
{
    #include "C:\Users\Egor\projects\processor\def_cmd.hpp"
};
#undef DEF_CMD

enum Regs_number
{
    ax = 1,
    bx = 2,
    cx = 3,
    dx = 4,
};

enum Args
{
    MASK      = 0b00011111,
    ARG_IMMED = 0b00100000,
    ARG_REG   = 0b01000000,
    ARG_MEM   = 0b10000000,
};

#endif