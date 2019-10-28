#include <stdio.h>
#include <AnastasLib\Enum.h>
#include <AnastasLib\Stack.h>
#include <assert.h>
#include <sys\stat.h>
#include <stdlib.h>
#include <cmath>

#define DEF_CMD(name, num, mode, code)      \
    case num: code; break;     \

const int RegNum = 8;
const int LenRAM = 500;
struct CPU
{
    FILE* f_in;
    int registers[RegNum];
    int RAM[LenRAM];
    int bufsize;
    char* buf;
    char* cur;
    Stack_t stk;
    Stack_t stkv;
};

void CPUconstruct (struct CPU* cpu, FILE* f_in, int bufsize);
void CPUdistruct (struct CPU* cpu);

int CPUdo (FILE* f_in);


int main () {

    setbuf (stdout, NULL);
    FILE* f_input = fopen (AsmFilesPathO, "rb");

    CPUdo(f_input);

    fclose (f_input);

    return 0;
}

int CPUdo (FILE* f_in) {


    struct stat FIN = {};
    if (fstat (fileno (f_in), &FIN) == -1 || FIN.st_size == 0) {
        printf("ERROR: Inadmissible or empty file\n");
        return 1;
    }

    CPU cpu;
    CPUconstruct (&cpu, f_in, FIN.st_size);

    fread (cpu.buf, sizeof (char), cpu.bufsize, cpu.f_in);

    StackPush (&cpu.stkv, cpu.bufsize - 1);

    while (*cpu.cur != CMD_ENDING) {
        switch (*cpu.cur) {
            #include <AnastasLib\commands.h>
            default:
                printf ("ERROR value = %d\n", *cpu.cur);
        }
    }

    printf ("%d\n", cpu.registers[0]);
    printf ("%d\n", cpu.registers[1]);
    printf ("%d\n", cpu.registers[2]);

    CPUdistruct (&cpu);

    return 0;
}

void CPUconstruct (struct CPU* cpu, FILE* f_in, int bufsize) {

    StackConstruct (cpu->stk)
    StackConstruct (cpu->stkv)

    cpu->registers[RegNum] = {};
    for (int i = 0; i < RegNum; i++)
        cpu->registers[i] = 0;

    cpu->RAM[LenRAM] = {};
    for (int i = 0; i < LenRAM; i++)
        cpu->RAM[i] = 0;

    cpu->bufsize = bufsize;
    cpu->buf = (char*) calloc (cpu->bufsize, sizeof (char));
    cpu->cur =cpu->buf;
    cpu->f_in = f_in;

}

void CPUdistruct (struct CPU* cpu) {

    free (cpu->stk.data);
    free (cpu->stkv.data);
    free (cpu->buf);
}

#undef DEF_CMD