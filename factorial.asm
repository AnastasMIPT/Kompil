IN
POP ax
PUUSH ax
CALL fact
OUT
RET
:fact
PUUSH ax
PUSH 1
JE next
PUSH 1
PUUSH ax
SUB
POP ax
PUUSH ax
CALL fact
MUL
:next
RET
ENDING