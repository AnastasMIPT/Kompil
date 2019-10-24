//
// Created by Admin on 16.10.2019.
//


#define DEF_CMD(name, num, mode, code)  \
    CMD_##name = num, \

enum Commands
{
#include <AnastasLib\commands.h>
    PRECISION = 100
};
#undef DEF_CMD


enum TypesOfArgument {
    NOARGUMENTS_T,
    IMMED_T,
    REGISTER_T,
    LABEL_T
};

const char* AsmFilesPathI = "F:\\Programming\\asm_files\\SolveSqueare.asm";
const char* AsmFilesPathO = "F:\\Programming\\asm_files\\output.ex";

