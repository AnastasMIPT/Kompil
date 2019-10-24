//
// Created by Admin on 15.10.2019.
//


DEF_CMD (PUSH, 1, IMMED_T, {
    printf ("%s ", "PUSH");
    printf ("%d\n", *((int*) (cur + 1)));
    StackPush (&stk, *((int*) (cur + 1)) * PRECISION);
    cur += sizeof (int);
    cur++;
//Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

})


DEF_CMD (PUUSH, 11, REGISTER_T, {
    printf ("%s ", "PUUSH");

    printf ("%d\n", registers[*(cur + 1) - 'a']);
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &stkv);

    StackPush (&stk, registers[*(cur + 1) - 'a']);

    //printf ("%d\n", registers[0]);
    //Dump (" ", stdout, 1, " ", &stk);
    cur += 3;
    cur++;
//Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

})

DEF_CMD (POP, 12, REGISTER_T, {
    printf ("%s\n", "POP");
    registers[*(cur + 1) - 'a'] = StackPop (&stk);
    cur += 3;
    cur++;
//Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

})

DEF_CMD (ADD, 2, NOARGUMENTS_T,
{
    printf ("%s\n", "ADD");
    StackPush (&stk, StackPop (&stk) + StackPop (&stk));
    cur++;
})

DEF_CMD (SUB, 3, NOARGUMENTS_T, {
    printf ("%s\n", "SUB");
    StackPush (&stk, StackPop (&stk) - StackPop (&stk));
    cur++;
})

DEF_CMD (MUL, 4, NOARGUMENTS_T, {
    printf ("%s ", "MUL");
//Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

int mul = StackPop (&stk) * StackPop (&stk) / PRECISION;
    printf ("%lf\n", mul / PRECISION);
    StackPush (&stk, mul);
//Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

cur++;
})


DEF_CMD (DIV, 5, NOARGUMENTS_T, {
    printf ("%s ", "DIV");
  //  Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);
    int a = StackPop (&stk);
    int b = PRECISION * StackPop (&stk);
   // printf ("%lf\n", (b / a));
    StackPush (&stk, b / a);
Dump ("????????", stdout, 1, " ", &stk);
    cur++;
})

DEF_CMD (SQRT, 6, NOARGUMENTS_T, {
    printf ("%s ", "SQRT");
    //  Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);
    double a = ((double) StackPop (&stk)) / PRECISION;
    int b = (int) (PRECISION * sqrt (a));
    // printf ("%lf\n", (b / a));
    StackPush (&stk, b);
    //Dump ("????????", stdout, 1, " ", &stk);
    cur++;
})


DEF_CMD (OUT, 9, NOARGUMENTS_T, {
    printf ("%s\n", "OUT");
    printf ("%.2lf\n", (double) StackPop (&stk)/ PRECISION);
    cur++;
})

DEF_CMD (IN, 10, NOARGUMENTS_T, {
    printf ("%s\n", "IN");
    int val;
    scanf ("%d", &val);
    StackPush (&stk, val * PRECISION);
    cur++;
})


DEF_CMD (JUMP, 21, LABEL_T, {
    printf ("%s ", "JUMP");
    int val = *(int*) (cur + 1);
    printf ("%d\n", val);
    cur = buf +  val;
})

DEF_CMD (JA, 22, LABEL_T, {
    printf ("%s ", "JA");
    int val = *(int*) (cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    if (StackPop (&stk) < StackPop (&stk))  cur = buf +  val;
    else cur += sizeof (int) + 1;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (JE, 26, LABEL_T, {
    printf ("%s ", "JE");
    int val = *(int*) (cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    if (StackPop (&stk) == StackPop (&stk))  cur = buf +  val;
    else cur += sizeof (int) + 1;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (JNE, 27, LABEL_T, {
    printf ("%s ", "JNE");
    int val = *(int*) (cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    if (StackPop (&stk) != StackPop (&stk))  cur = buf +  val;
    else cur += sizeof (int) + 1;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (CALL, 31, LABEL_T, {
    printf ("%s ", "CALL");
    int val = *(int*) (cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    StackPush (&stkv, (int) (cur + sizeof (int) + 1 - buf));
    cur = buf +  val;
    //Dump (" ", stdout, 2, " ",&stkv);
})

DEF_CMD (RET, 32, NOARGUMENTS_T, {
    printf ("%s ", "RET");
    //Dump (" ", stdout, 2, " ",&stk);
    int val = StackPop (&stkv);
    printf (" %d\n", val);
    cur = buf +  val;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (ENDING, 28, NOARGUMENTS_T, ;)