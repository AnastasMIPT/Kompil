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
PUSH 2
OUT

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
SQRT

OUT
RET
ENDING