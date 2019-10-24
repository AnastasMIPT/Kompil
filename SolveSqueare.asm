IN
IN
IN
POP cx
POP bx
POP ax

PUSH 0
PUUSH ax
JNE axnotnull

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

:axnotnull
PUSH 2
OUT

RET
ENDING