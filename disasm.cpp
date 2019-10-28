#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <AnastasLib\Enum.h>
//#include <stdlib.h>
#include <sys\stat.h>

#define DEF_CMD(name, num, mode, code)                  \
                                                        \
    if ((int) *ptr == CMD_##name) {                     \
        fprintf (f_out, "%s ", #name);                  \
        if (mode == NOARGUMENTS_T)                      \
            fprintf (f_out, "");                     \
        else if (mode == IMMED_T) {                     \
            fprintf (f_out, "%d", *(int*) (ptr + 1)); \
            ptr += sizeof (int);                        \
        }                                               \
        else if (mode == REGISTER_T) {                  \
            fprintf (f_out, "%cx", *(ptr + 1));       \
            ptr++;                                      \
        }                                               \
        else if (mode == LABEL_T) {                  \
            fprintf (f_out, "%d", *(int*)(ptr + 1));       \
            ptr += sizeof (int);                       \
        }                                               \
        fprintf (f_out, "\n");\
                                                  \
     }                                                  \
                                                        \

FILE* DISASM (FILE* f_in, FILE* f_out);

int main () {

    FILE* f_inp = fopen (AsmFilesPathO, "rb");
    FILE* f_outp = fopen (DisAsmFilesPathO, "w");

    assert (f_inp);
    assert (f_outp);

    DISASM (f_inp, f_outp);


    return 0;
}

FILE* DISASM (FILE* f_in, FILE* f_out) {

    int c;
    struct stat FIN = {};
    if (fstat (fileno (f_in), &FIN) == -1 || FIN.st_size == 0) {
        printf("ERROR: Inadmissible or empty file\n");
        return nullptr;
    }
    fstat (fileno (f_in), &FIN);

    char* buf = (char*) calloc (FIN.st_size, sizeof (char));
    fread (buf, sizeof (char), FIN.st_size, f_in);
    char* ptr = buf;
    while ((int) *ptr != CMD_ENDING ) {
        #include <AnastasLib\commands.h>
        ptr++;
    }

    fprintf (f_out, "ENDING\n");

    return f_out;
}