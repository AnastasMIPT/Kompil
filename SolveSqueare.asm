IN
IN
IN
POP cx
POP bx
POP ax

PUSH 0

PUUSH ax
JNE axnotnull
CALL linenoeur

:axnotnull

PUSH 0
PUUSH bx
JNE bnotnull
PUSH -1
PUUSH cx
MUL
POP cx

PUUSH cx
PUUSH ax
DIV
SQRT

PUSH 1
OUT
OUT

RET

:bnotnull

CALL diskriminant

PUSH 0
PUUSH dx
JNE dxnotnull
PUSH -1
PUUSH bx
MUL
PUSH 2
PUUSH ax
MUL
DIV

PUSH 1
OUT
OUT

RET

:dxnotnull



RET


:linenoeur
PUSH 0
PUUSH bx
JNE bxnotnull

PUSH 0
OUT
RET

:bxnotnull
PUSH -1
PUUSH cx
MUL
POP cx

PUUSH cx
PUUSH bx
DIV
OUT

RET

:diskriminant

PUUSH cx
PUUSH ax
PUSH 4
MUL
MUL
PUUSH bx
PUUSH bx
MUL
SUB
POP dx

RET

ENDING