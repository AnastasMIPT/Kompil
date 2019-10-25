#include <stdio.h>
#include <string.h>
#include <AnastasLib\Stack.h>
#include <AnastasLib\Enum.h>
#include <stdlib.h>
#include <sys\stat.h>


#define DEF_CMD(name, num, mode, code)                                          \
                                                                                \
    if (strcmp (command, #name) == 0) {                                         \
        *(char*) ptr = (char) CMD_##name;                                       \
        ptr++;                                                                  \
        ptr = CommandAnalizator (file_in, ptr, labels, arg, buf, mode);         \
}                                                                               \


struct Label
{
    char* Name;
    char* Value;
};

const int LenArgument = 11;
const int LenCommand = 7;
const int Nlabels = 10;
const int LenLabels = 10;
const double rat = 1.5;

FILE* ASM (FILE* file_in, FILE* file_out);
char* CommandAnalizator (FILE* logs, char* ptr, Label* labels, char * arg, char* buf, int mode);


int main () {

    FILE* f_in = fopen (AsmFilesPathI , "r");
    FILE* f_out = fopen (AsmFilesPathO , "wb");

    assert (f_in);
    assert (f_out);

    ASM (f_in, f_out);

    fclose (f_in);
    fclose (f_out);

    return 0;
}

FILE* ASM (FILE* file_in, FILE* file_out) {

    char command[LenCommand] = {};
    char  arg[LenArgument] = {};

    struct stat FIN = {};
    fstat (fileno (file_in), &FIN);


    char* buf = (char*) calloc (FIN.st_size / rat, sizeof (char));
    if (!buf) printf ("ERROR, impossible to get memory to buffer");
    //assert (buf);
    char* ptr = buf;

    char* str = (char*) calloc (10, sizeof (char));
    memset (str, 0, LenLabels * sizeof (char));
    Label labels[Nlabels];

    for (int i = 0; i < Nlabels; i++) {
        labels[i].Name = (char*) calloc (LenLabels, sizeof (char));
        memset (labels[i].Name, 0, LenLabels * sizeof (char));
    }

    int NumLabel = 0;
    for (int j = 0; j != 2; j++) {
        ptr = buf;
        memset (command, 0, LenCommand * sizeof (char));
        fseek (file_in, 0, SEEK_SET);

        while (strcmp(command, "ENDING") != 0) {
            memset(arg, 0, LenArgument);
            fscanf(file_in, "%s", command);
            fprintf(stdout, "%s ", command);
            #include <AnastasLib/commands.h>
            if (j == 0) {
                if (*command == ':' && (NumLabel == 0 || strcmp(labels[NumLabel - 1].Name, command) != 0)) {
                    printf("\n");
                    strcpy(labels[NumLabel].Name, command + 1);
                    labels[NumLabel].Value = ptr;
                    NumLabel++;
                }
            }
        }
    }

    int SizeBuf = (int) (ptr - buf);
    fwrite (buf, sizeof (char), SizeBuf, file_out);
    free (buf);

    return file_out;
}
#undef DEF_CMD

char* CommandAnalizator (FILE* code, char* ptr, Label* labels, char * arg, char* buf, int mode) {

    switch (mode) {
            case NOARGUMENTS_T:
                printf ("\n");
                break;
            case IMMED_T:
                fscanf (code, "%s", arg);
                printf ("%s\n", arg);
                *(int*) ptr = atoi(arg);
                ptr += sizeof(int);
                break;
            case REGISTER_T:
                fscanf (code, "%s", arg);
                printf ("%s\n", arg);

                for (int i = 0; arg[i] != '\0'; ptr++, i++)
                    *ptr = arg[i];

                *ptr = '\0';
                ptr++;
                break;
            case LABEL_T:
                fscanf (code, "%s", arg);
                printf ("%s\n", arg);

                for (int i = 0; *labels[i].Name != '\0' && i < Nlabels; i++) {

                    if (strcmp (labels[i].Name, arg) == 0) {

                        *(int*) ptr = (int) (labels[i].Value - buf);
                        break;
                     }
                }
                printf ("%d\n", *(int*) ptr);
                ptr += sizeof (int);
                break;
        }

    return ptr;
}