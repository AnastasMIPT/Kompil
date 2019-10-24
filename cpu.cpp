#include <stdio.h>
#include <AnastasLib\Enum.h>
#include <AnastasLib\StackStatic.h>
#include <assert.h>
#include <sys\stat.h>
#include <stdlib.h>

#define DEF_CMD(name, num, mode, code)      \
    case num: code; break;     \


int CPU (FILE* f_in);

const int RegNum = 8;

int main () {


    setbuf (stdout, NULL);
    FILE* f_input = fopen (AsmFilesPathO, "rb");

    CPU (f_input);

    return 0;
}

int CPU (FILE* f_in) {

//    Testing();
    struct stat FIN = {};

    if (fstat (fileno (f_in), &FIN) == -1 || FIN.st_size == 0) {
        printf("ERROR: Inadmissible or empty file\n");
        return 1;
    }

    char* buf = (char*) calloc (FIN.st_size, sizeof (char));

    if (!buf) printf ("ERROR: impossible to get memery for buffer");
    assert (buf);

    char* cur = buf;

    fread (buf, sizeof (char), FIN.st_size, f_in);

    Stack_t stk;
    StackConstruct (stk)

    Stack_t stkv;
    StackConstruct (stkv)

    StackPush (&stkv, FIN.st_size - 1);

    int registers[RegNum] = {};


    while (*cur != CMD_ENDING) {
        switch (*cur) {
            #include <AnastasLib\commands.h>
            default:
                printf ("ERROR value = %d\n", *cur);
        }
    }

    //printf ("%d\n", StackPop (&stk));
    printf ("%d\n", registers[0]);
    printf ("%d\n", registers[1]);
    printf ("%d\n", registers[2]);

    //free(malloc(100));
    //free(&stkv);
    return 0;
}

#undef DEF_CMD