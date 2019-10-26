//
// Created by Admin on 15.10.2019.
//


DEF_CMD (PUSH, 1, IMMED_T, {
    printf ("%s ", "PUSH");
    printf ("%d\n", *((int*) (cpu.cur + 1)));
    StackPush (&cpu.stk, *((int*) (cpu.cur + 1)) * PRECISION);
    cpu.cur += sizeof (int);
    cpu.cur++;
//Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stk);

})


DEF_CMD (PUUSH, 11, REGISTER_T, {
    printf ("%s ", "PUUSH");

    printf ("%d\n", cpu.registers[*(cpu.cur + 1) - 'a']);
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stkv);

    StackPush (&cpu.stk, cpu.registers[*(cpu.cur + 1) - 'a']);

    //printf ("%d\n", cpu.registers[0]);
    //Dump (" ", stdout, 1, " ", &cpu.stk);
    cpu.cur += 3;
    cpu.cur++;
//Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stk);

})

DEF_CMD (POP, 12, REGISTER_T, {
    printf ("%s\n", "POP");
    cpu.registers[*(cpu.cur + 1) - 'a'] = StackPop (&cpu.stk);
    cpu.cur += 3;
    cpu.cur++;
//Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

})

DEF_CMD (ADD, 2, NOARGUMENTS_T,
{
    printf ("%s\n", "ADD");
    StackPush (&cpu.stk, StackPop (&cpu.stk) + StackPop (&cpu.stk));
    cpu.cur++;
})

DEF_CMD (SUB, 3, NOARGUMENTS_T, {
    printf ("%s\n", "SUB");
    StackPush (&cpu.stk, StackPop (&cpu.stk) - StackPop (&cpu.stk));
    cpu.cur++;
})

DEF_CMD (MUL, 4, NOARGUMENTS_T, {
    printf ("%s ", "MUL");
//Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

int mul = StackPop (&cpu.stk) * StackPop (&cpu.stk) / PRECISION;
    printf ("%lf\n", (double) mul / PRECISION);
    StackPush (&cpu.stk, mul);
//Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

    cpu.cur++;
})


DEF_CMD (DIV, 5, NOARGUMENTS_T, {
    printf ("%s ", "DIV");
    Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stk);
    int a = StackPop (&cpu.stk);
    int b = PRECISION * StackPop (&cpu.stk);
   // printf ("%lf\n", (b / a));
    StackPush (&cpu.stk, b / a);
Dump ("????????", stdout, 1, " ", &cpu.stk);
    cpu.cur++;
})

DEF_CMD (SQRT, 6, NOARGUMENTS_T, {
    printf ("%s ", "SQRT");
    //  Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);
    double a = ((double) StackPop (&cpu.stk)) / PRECISION;
    int b = (int) (PRECISION * sqrt (a));
    printf ("%d\n", b);
    StackPush (&cpu.stk, b);
    //Dump ("????????", stdout, 1, " ", &stk);
    cpu.cur++;
})


DEF_CMD (OUT, 9, NOARGUMENTS_T, {
    printf ("%s\n", "OUT");
    printf ("%.2lf\n", (double) StackPop (&cpu.stk)/ PRECISION);
    cpu.cur++;
})

DEF_CMD (IN, 10, NOARGUMENTS_T, {
    printf ("%s\n", "IN");
    int val;
    scanf ("%d", &val);
    StackPush (&cpu.stk, val * PRECISION);
    cpu.cur++;
})


DEF_CMD (JUMP, 21, LABEL_T, {
    printf ("%s ", "JUMP");
    int val = *(int*) (cpu.cur + 1);
    printf ("%d\n", val);
    cpu.cur = cpu.buf +  val;
})

DEF_CMD (JA, 22, LABEL_T, {
    printf ("%s ", "JA");
    int val = *(int*) (cpu.cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    if (StackPop (&cpu.stk) < StackPop (&cpu.stk))  cpu.cur = cpu.buf +  val;
    else cpu.cur += sizeof (int) + 1;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (JE, 26, LABEL_T, {
    printf ("%s ", "JE");
    int val = *(int*) (cpu.cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    if (StackPop (&cpu.stk) == StackPop (&cpu.stk))  cpu.cur = cpu.buf +  val;
    else cpu.cur += sizeof (int) + 1;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (JNE, 27, LABEL_T, {
    printf ("%s ", "JNE");
    int val = *(int*) (cpu.cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    if (StackPop (&cpu.stk) != StackPop (&cpu.stk))  cpu.cur = cpu.buf +  val;
    else cpu.cur += sizeof (int) + 1;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (CALL, 31, LABEL_T, {
    printf ("%s ", "CALL");
    int val = *(int*) (cpu.cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    StackPush (&cpu.stkv, (int) (cpu.cur + sizeof (int) + 1 - cpu.buf));
    cpu.cur = cpu.buf +  val;
    //Dump (" ", stdout, 2, " ",&stkv);
})

DEF_CMD (RET, 32, NOARGUMENTS_T, {
    printf ("%s ", "RET");
    //Dump (" ", stdout, 2, " ",&stk);
    int val = StackPop (&cpu.stkv);
    printf (" %d\n", val);
    cpu.cur = cpu.buf +  val;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (ENDING, 28, NOARGUMENTS_T, ;)