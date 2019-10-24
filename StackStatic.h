#include <stdio.h>
#include <assert.h>
#include <cstring>

#define StackConstruct(stk)                                             \
{                                                                       \
    memset (stk.data, 0, sizeof (el_t) * NElements);                    \
    stk.size = 0;                                                       \
    stk.err  = 0;                                                       \
    stk.Name = #stk;                                                    \
                                                                        \
                                                                        \
}                                                                       \

#define ASSERT_OK(stk)                                                                \
{                                                                                     \
    if(StackOK (stk, &(stk->err)))                                                    \
        Dump ("\nStack Information", stdout, __LINE__, __FILE__, stk);                \
}                                                                                     \

typedef long long el_t;
const int NElements = 10;
const int NChars = 1001;

struct Stack_t
{
    el_t data[NElements];
    int size;
    int err;
    char* Name;
};

bool StackPush (Stack_t* stk, el_t value);
el_t StackPop (Stack_t* stk);
int  StackOK (const Stack_t* stk, int* err);
void Dump (char * FirstString, FILE* file, int NumLine, char* NameOfFile, Stack_t* stk);


bool StackPush (Stack_t* stk, el_t value) {

    ASSERT_OK (stk);

    stk->data[stk->size++] = value;

    ASSERT_OK (stk);
    return true;
}

el_t StackPop (Stack_t* stk) {

    ASSERT_OK (stk);
    stk->data[stk->size] = -667766;
    --stk->size;
    ASSERT_OK (stk);
    return stk->data[stk->size];
}

int  StackOK (const Stack_t* stk, int* err) {

    if (!stk)
        *err = 1;
    if (stk->size > NElements - 1)
        *err = 2;
    if (stk->size < 0)
        *err = 3;
    return *err;
}

/*! Функция для вывода инвормации о стеке stack
*
*	@param [in] FirstString Cтрока, выводящаяся в начале
*	@param [in] file Указатель на файл, в который выводится информация
*	@param [in] NumLine Номер строки, с которой была вызвана функция
*	@param [in] NameOfFile Имя файла, из которого была вызвана функция
*	@param [in] stk Указатель на стек
*
*/
void Dump (char * FirstString, FILE* file, int NumLine, char* NameOfFile, Stack_t* stk) {

    assert (file);


    fprintf(file, "%s\n%s(%d)\n", FirstString, NameOfFile, NumLine);

    switch (stk->err) {
        case 0:
            fprintf(file, "err = 0 (ok)\n");
            break;
        case 1:
            fprintf(file, "err = 1 (ERROR)\n"
                          "Ошибка:  Нулевой указатель на стек\n");
            break;
        case 2:
            fprintf(file, "err = 2 (ERROR)\n"
                          "Ошибка:  Переполнение стека\n");
            break;
        case 3:
            fprintf(file, "err = 3 (ERROR)\n"
                          "Ошибка:  Попытка изъятия из пустого стека\n");
            break;
    }
    fprintf(file, "Stack_t %s [%p]\n"
                  "{\n"
                  "size = %d\n"
                  "data[%d] = [%p]\n"
                  "    {\n", stk->Name, stk, stk->size, NChars, stk->data);

    for (int i = 0; i < NElements; i++) {
        if (i < stk->size)
            fprintf(file, "    *");
        else
            fprintf(file, "     ");
        fprintf(file, "[%d] = %lld\n", i, stk->data[i]);
    }

    fprintf (file, "    }\n"
                   "}");
}
