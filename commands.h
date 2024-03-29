//
// Created by Admin on 15.10.2019.
//

#define POP StackPop (&cpu.stk)
#define PUSH(code) StackPush (&cpu.stk, code);

DEF_CMD (PUSH, 1, IMMED_T, {
    printf ("%s ", "PUSH");
    printf ("%d\n", *((int*) (cpu.cur + 1)));
    PUSH (*((int*) (cpu.cur + 1)) * PRECISION);
    cpu.cur += sizeof (int);
    cpu.cur++;
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stk);

})


DEF_CMD (PUSHR, 11, REGISTER_T, {
    printf ("%s ", "PUSHR");

    printf ("%d\n", cpu.registers[*(cpu.cur + 1) - 'a']);
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stkv);

    PUSH (cpu.registers[*(cpu.cur + 1) - 'a']);
    //Dump (" ", stdout, 1, " ", &cpu.stk);

    cpu.cur += 2;
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stk);

})

DEF_CMD (PUSHRAM, 21, RAM_T, {
    printf ("%s ", "PUSHRAM");

    printf ("%d\n", cpu.RAM[cpu.registers[*(cpu.cur + 1) - 'a'] / PRECISION + *(int*) (cpu.cur + 2)]);

    //Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stkv);


    PUSH (cpu.RAM[cpu.registers[*(cpu.cur + 1) - 'a'] / PRECISION + *(int*) (cpu.cur + 2)]);

    //Dump (" ", stdout, 1, " ", &cpu.stk);
    cpu.cur += sizeof (int);
    cpu.cur += 2;
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stk);

})

DEF_CMD (PUSHRAMREG, 31, RAM_T, {
    printf ("%s ", "PUSHRAMREG");

    printf ("%d\n", cpu.RAM[cpu.registers[*(cpu.cur + 1) - 'a'] / PRECISION]);
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stkv);

    PUSH (cpu.RAM[cpu.registers[*(cpu.cur + 1) - 'a'] / PRECISION]);

    //Dump (" ", stdout, 1, " ", &cpu.stk);
    cpu.cur += 2;
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stk);

})

DEF_CMD (PUSHRAMD, 41, RAM_T, {
    printf ("%s ", "PUSHRAMD");

    printf ("%d\n", cpu.RAM[*(int*) (cpu.cur + 1)]);
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stkv);

    PUSH (cpu.RAM[*(int*) (cpu.cur + 1)]);

    //Dump (" ", stdout, 1, " ", &cpu.stk);
    cpu.cur += sizeof (int);
    cpu.cur++;
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stk);

})

DEF_CMD (POP, 12, REGISTER_T, {
    printf ("%s\n", "POP");
    cpu.registers[*(cpu.cur + 1) - 'a'] = POP;
    cpu.cur += 2;
//Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

})

DEF_CMD (POPRAM, 22, RAM_T, {
    printf ("%s\n", "POPRAM");
    cpu.RAM[cpu.registers[*(cpu.cur + 1) - 'a'] / PRECISION + *(int*) (cpu.cur + 2)] = POP;
    cpu.cur += sizeof (int);
    cpu.cur += 2;
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

})

DEF_CMD (POPRAMREG, 32, RAM_T, {
    printf ("%s\n", "POPRAMREG");
    cpu.RAM[cpu.registers[*(cpu.cur + 1) - 'a'] / PRECISION] = POP;
    cpu.cur += 2;
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

})

DEF_CMD (POPRAMD, 42, RAM_T, {
    printf ("%s\n", "POPRAMD");
    cpu.RAM[*(int*) (cpu.cur + 1)] = POP;
    cpu.cur += sizeof (int);
    cpu.cur++;
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

})


DEF_CMD (ADD, 2, NOARGUMENTS_T,
{
    printf ("%s\n", "ADD");
    PUSH (POP + POP);
    cpu.cur++;
})

DEF_CMD (SUB, 3, NOARGUMENTS_T, {
    printf ("%s\n", "SUB");
    PUSH (POP - POP);
    cpu.cur++;
})

DEF_CMD (MUL, 4, NOARGUMENTS_T, {
    printf ("%s ", "MUL");
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

    int mul = POP * POP / PRECISION;
    printf ("%lf\n", (double) mul / PRECISION);
    PUSH (mul);
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);

    cpu.cur++;
})


DEF_CMD (DIV, 5, NOARGUMENTS_T, {
    printf ("%s ", "DIV");
    //Dump ("&&&&&&&&&&", stdout, 1, " ", &cpu.stk);
    int a = POP;
    int b = PRECISION * POP;
    // printf ("%lf\n", (b / a));
    PUSH (b / a);
    //Dump ("????????", stdout, 1, " ", &cpu.stk);
    cpu.cur++;
})

DEF_CMD (SQRT, 6, NOARGUMENTS_T, {
    printf ("%s ", "SQRT");
    //  Dump ("&&&&&&&&&&", stdout, 1, " ", &stk);
    double a = ((double) POP) / PRECISION;
    int b = (int) (PRECISION * sqrt (a));
    printf ("%d\n", b);
    PUSH (b);
    //Dump ("????????", stdout, 1, " ", &stk);
    cpu.cur++;
})


DEF_CMD (OUT, 9, NOARGUMENTS_T, {
    printf ("%s\n", "OUT");
    printf ("%.2lf\n", (double) POP/ PRECISION);
    cpu.cur++;
})

DEF_CMD (IN, 10, NOARGUMENTS_T, {
    printf ("%s\n", "IN");
    int val;
    scanf ("%d", &val);
    PUSH (val * PRECISION);
    cpu.cur++;
})


DEF_CMD (JUMP, 23, LABEL_T, {
    printf ("%s ", "JUMP");
    int val = *(int*) (cpu.cur + 1);
    printf ("%d\n", val);
    cpu.cur = cpu.buf +  val;
})

DEF_CMD (JA, 24, LABEL_T, {
    printf ("%s ", "JA");
    int val = *(int*) (cpu.cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    if (POP < POP)  cpu.cur = cpu.buf +  val;
    else cpu.cur += sizeof (int) + 1;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (JE, 26, LABEL_T, {
    printf ("%s ", "JE");
    int val = *(int*) (cpu.cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    if (POP == POP)  cpu.cur = cpu.buf +  val;
    else cpu.cur += sizeof (int) + 1;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (JNE, 27, LABEL_T, {
    printf ("%s ", "JNE");
    int val = *(int*) (cpu.cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    if (POP != POP)  cpu.cur = cpu.buf +  val;
    else cpu.cur += sizeof (int) + 1;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (CALL, 33, LABEL_T, {
    printf ("%s ", "CALL");
    int val = *(int*) (cpu.cur + 1);
    printf ("%d\n", val);
    //Dump (" ", stdout, 2, " ",&stk);
    StackPush (&cpu.stkv, (int) (cpu.cur + sizeof (int) + 1 - cpu.buf));
    cpu.cur = cpu.buf +  val;
    //Dump (" ", stdout, 2, " ",&stkv);
})

DEF_CMD (RET, 34, NOARGUMENTS_T, {
    printf ("%s ", "RET");
    //Dump (" ", stdout, 2, " ",&stk);
    int val = StackPop (&cpu.stkv);
    printf (" %d\n", val);
    cpu.cur = cpu.buf +  val;
    //Dump (" ", stdout, 2, " ",&stk);
})


DEF_CMD (ENDING, 28, NOARGUMENTS_T, ;)