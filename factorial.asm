IN
POP ax
PUSHR ax
CALL fact
OUT
RET
:fact
PUSHR ax
PUSH 1
JE next
PUSH 1
PUSHR ax
SUB
POP ax
PUSHR ax
CALL fact
MUL
:next
RET
ENDING