#include <stdio.h>
#include <assert.h>
#include <cstring>
#include <cstdlib>

#define StackConstruct(stk)                                            \
{                                                                       \
    StackConstructor (&stk, #stk);                                      \
}                                                                       \

#define ASSERT_OK(stk)                                                                \
{                                                                                     \
    if(StackOK (stk))                                                                 \
        Dump ("\nStack Information", stdout, __LINE__, __FILE__, stk);                \
}                                                                                     \

typedef int el_t;
const int NChars  = 10;
const el_t Poison = -667766;
const double k_up = 2;
const int delta   = 3;
const long long CANARY  = 123456789123456789;


struct Stack_t
{
    long long Canary1;
    el_t* data;
    int NElements;
    int size;
    int err;
    char* Name;
    long long HASH;
    long long Canary2;
};

bool StackPush (Stack_t* stk, el_t value);
bool TestStackPush ();
el_t StackPop (Stack_t* stk);
bool TestStackPop ();
int  StackOK (Stack_t* stk);
Stack_t* StackMemUp (Stack_t* stk);
bool TestStackMemUp ();
Stack_t* StackMemDown (Stack_t* stk);
void Dump (char * FirstString, FILE* file, int NumLine, char* NameOfFile, Stack_t* stk);
int Hash (Stack_t* stk);
void CHECK_Hash (int MustBe, int* count, int TestNum);
bool TestHash ();
int Testing();
void StackConstructor (Stack_t* stk, char* Name);


void StackConstructor (Stack_t* stk, char* Name) {

    stk->NElements = 10;

    stk->data = (el_t*) calloc (stk->NElements, sizeof (el_t));

    memset (stk->data, 0, sizeof (el_t) * stk->NElements);
    stk->Canary1   = CANARY;
    stk->Canary2   = CANARY;
    stk->size      = 0;
    stk->err       = 0;
    stk->Name      = Name;
    stk->HASH      = 0;

    for (int i = 0; stk->data + i < stk->data + stk->NElements; i++)
        stk->data[i] = Poison;

}

/*! Функция, запускающая тестирующие функции
*
*	@return Успшно ли прошло тестирование
*
*/

int Testing ()
{
    int col_OK = 0;

    if (TestStackPush ()) {
        printf("StackPush (): OK\n");
        col_OK++;
    }
    if (TestStackPop ()) {
        printf ("StackPop (): OK\n");
        col_OK++;
    }
    if (TestHash ()) {
        printf("Hash (): OK\n");
        col_OK++;
    }
    if (TestStackMemUp ()) {
        printf("StackMemUp (): OK\n");
        col_OK++;
    }


    return col_OK == 4;
}


/*! Функция, cчитающая хеш стека stk
*
*	@param [in] stk указатель на стек
*
*/
//long long

int Hash (Stack_t* stk) {
    int hash = 0;
    for (int i = 0; i < stk->size; i++)
        hash = hash + (stk->data[i] >> 3 | 1233);

    return hash;
}


void CHECK_Hash (Stack_t* stack, int MustBe, int* count, int TestNum) {
    if (Hash (stack) != MustBe)
        printf ("Hash(): test failed %d\n", TestNum);
    else
        (*count)++;
}
bool TestHash () {

    int count = 0;
    Stack_t stkH;
    StackConstruct (stkH);

    stkH.data[0] = 54;
    stkH.data[1] = 512;
    stkH.data[2] = 23;
    stkH.data[3] = -1230;
    stkH.size = 4;

    CHECK_Hash (&stkH, 3698, &count, 1);

    stkH.data[4] = -232;
    stkH.data[5] = -20;
    stkH.size = 6;

    CHECK_Hash(&stkH, 3682, &count, 2);

    return count == 2;
}

/*! Функция, выделяющая дополнительную память для стека
*
*	@param [in] stk указатель на стек
*
*/
Stack_t* StackMemUp (Stack_t* stk) {

    ASSERT_OK (stk);

    int NewSize = k_up * stk->NElements;
    stk->data = (el_t*) realloc (stk->data, NewSize * sizeof(el_t));

    for (int i = stk->NElements; i < stk->NElements + (k_up - 1) * stk->NElements; i++)
        stk->data[i] = Poison;

    stk->NElements *= k_up;

    ASSERT_OK (stk);

    return stk;
}

bool TestStackMemUp () {

    int count = 0;
    Stack_t stkMU;
    StackConstruct (stkMU);

    StackMemUp (&stkMU);
    if (stkMU.NElements != 10 * k_up) {
        printf ("StackMemUp(): test failed №1");
        count++;
    }
    if (!stkMU.data) {
        printf ("StackMemUp(): test failed №2");
        count++;
    }
    if (stkMU.data[12] != Poison) {
        printf ("StackMemUp(): test failed №3");
        count++;
    }

    return count == 0;
}
/*! Функция, освобождающая память
*
*	@param [in] stk указатель на стек
*
*/
Stack_t* StackMemDown (Stack_t* stk) {

    ASSERT_OK (stk);

    int NewSize = (1 / k_up) * stk->NElements;
    stk->data = (el_t*) realloc (stk->data, (delta + NewSize)  * sizeof(el_t));
    stk->NElements = delta + NewSize;

    ASSERT_OK (stk);
}

/*! Функция, добавляющая новый элемент в стек
*
*	@param [in] stk указатель на стек
*	@param [in] value значение элемента
*
*/
bool StackPush (Stack_t* stk, el_t value) {

    ASSERT_OK (stk);

    stk->data[stk->size++] = value;

    stk->HASH = Hash (stk);

    if (stk->size == stk->NElements)
        StackMemUp(stk);

    ASSERT_OK (stk);
    return true;
}

bool TestStackPush () {


    int count = 0;
    Stack_t stkPu = {};
    StackConstruct (stkPu);

    StackPush (&stkPu,12);
    if (stkPu.size != 1 || stkPu.data[0] != 12)
        printf ("StackPush(): test failed 1\n");
    else
        count++;

    StackPush (&stkPu,1223342);
    if (stkPu.size != 2 || stkPu.data[1] != 1223342)
        printf ("StackPush(): test failed 2\n");
    else
        count++;

    StackPush (&stkPu,-2345);
    if (stkPu.size != 3 || stkPu.data[2] != -2345)
        printf ("StackPush(): test failed 3\n");
    else
        count++;

    if (stkPu.data[3] != Poison)
        printf ("StackPush(): test failed 4\n");
    else
        count++;

    if (stkPu.HASH != 153985)
        printf ("StackPush(): test failed 5\n");
    else
        count++;

    return count == 5;
}

/*! Функция, берущая элемент из стека
*
*	@param [in] stk указатель на стек
*
*/
el_t StackPop (Stack_t* stk) {

    ASSERT_OK (stk);

    --stk->size;
    el_t elem = stk->data[stk->size];
    stk->data[stk->size] = Poison;

    stk->HASH = Hash (stk);

    if (stk->size < (1 / k_up) * stk->NElements)
        StackMemDown (stk);

    ASSERT_OK (stk);

    return elem;
}

bool TestStackPop () {

    int count = 0;

    Stack_t stkPo = {};
    StackConstruct (stkPo);

    stkPo.data[0] = 54;
    stkPo.data[1] = 512;
    stkPo.data[2] = 23;
    stkPo.data[3] = -1230;
    stkPo.size = 4;
    stkPo.HASH = Hash (&stkPo);
    el_t x = StackPop (&stkPo);

    if (x != -1230)
        printf ("StackPop(): test failed 1\n");
    else
        count++;

    if (stkPo.size != 3)
        printf ("StackPop(): test failed 2\n");
    else
        count++;

    el_t y = StackPop (&stkPo);

    if (y != 23)
        printf ("StackPop(): test failed 3\n");
    else
        count++;

    if (stkPo.size != 2)
        printf ("StackPop(): test failed 4\n");
    else
        count++;

    if (stkPo.HASH != 2472)
        printf ("StackPop(): test failed 5\n");
    else
        count++;

    return count == 5;
}

/*! Функция, проверяющая корректность стека
*
*	@param [in] stk указатель на стек
*	@param [in] err Указатель на файл, в который выводится информация
*	@param [in] NumLine Номер строки, с которой была вызвана функция
*	@param [in] NameOfFile Имя файла, из которого была вызвана функция
*	@param [in] stk Указатель на стек
*
*/
int  StackOK (Stack_t* stk) {

    if (!stk)
        stk->err = 1;
    if (stk->size > stk->NElements)
        stk->err = 2;
    if (stk->size < 0)
        stk->err = 3;
    if (stk->Canary1 != CANARY || stk->Canary2 != CANARY)
        stk->err = 4;
    if (Hash (stk) != stk->HASH)
        stk->err = 5;
    return stk->err;
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

    fprintf (file, "%s\n%s(%d)\n", FirstString, NameOfFile, NumLine);

    switch (stk->err) {
        case 0:
            fprintf (file, "err = 0 (ok)\n");
            break;
        case 1:
            fprintf (file, "err = 1 (ERROR)\n"
                           "ERROR:  Nullptr on stack\n");
            break;
        case 2:
            fprintf (file, "err = 2 (ERROR)\n"
                           "ERROR:  Stack overflow\n");
            break;
        case 3:
            fprintf (file, "err = 3 (ERROR)\n"
                           "ERROR:  Attempting to access an empty stack\n");
            break;
        case 4:
            fprintf (file, "err = 4 (ERROR)\n"
                           "ERROR:  The stack structure is damaged\n");
            break;
        case 5:
            fprintf (file, "err = 5 (ERROR)\n"
                           "ERROR:  Stack elements are damaged!\n");
            break;

    }

    fprintf (file, "Stack_t %s [%p]\n"
                   "{\n"
                   "size = %d\n"
                   "Hash = %d\n"
                   "HASH = %d\n"
                   "data[%d] = [%p]\n"
                   "    {\n", stk->Name, stk, stk->size, Hash (stk), stk->HASH, NChars, stk->data);

    for (int i = 0; i < stk->NElements; i++) {
        if (i < stk->size)
            fprintf (file, "    *");
        else
            fprintf (file, "     ");
        fprintf (file, "[%d] = %d", i, stk->data[i]);

        if (stk->data[i] == Poison)
            fprintf (file, "  [Poison]\n");
        else
            fprintf (file, "\n");
    }

    fprintf (file, "    }\n"
                   "}\n");
}
