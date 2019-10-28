IN
IN
IN
POP cx
POP bx
POP ax

PUSH 0

PUSHR ax
JNE axnotnull

CALL linenoeur
RET
:axnotnull
PUSH 0
PUSHR bx
JNE bnotnull
PUSH -1
PUSHR cx
MUL
POP cx

PUSHR cx
PUSHR ax
DIV
SQRT

PUSH 1
OUT
OUT

RET

:bnotnull

CALL diskriminant

PUSH 0
PUSHR dx
JNE dxnotnull
PUSH -1
PUSHR bx
MUL
PUSH 2
PUSHR ax
MUL
DIV

PUSH 1
OUT
OUT

RET

:dxnotnull

PUSHR dx
PUSH 0
JA nex
PUSH 0
OUT
RET
:nex

PUSHR dx
SQRT
PUSH -1
PUSHR bx
MUL
ADD
PUSH 2
PUSHR ax
MUL
DIV

PUSHR dx
SQRT
PUSH -1
PUSHR bx
MUL
SUB
PUSH 2
PUSHR ax
MUL
DIV

PUSH 2
OUT
OUT
OUT

RET


:linenoeur
PUSH 0
PUSHR bx
JNE bxnotnull

PUSH 0
OUT
RET

:bxnotnull
PUSH -1
PUSHR cx
MUL
POP cx

PUSHR cx
PUSHR bx
DIV
PUSH 1
OUT
OUT

RET

:diskriminant

PUSHR cx
PUSHR ax
PUSH 4
MUL
MUL
PUSHR bx
PUSHR bx
MUL
SUB
POP dx

RET

ENDING