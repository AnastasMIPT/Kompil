PUSH 1
POP ax
:next
PUSHR ax
PUSH 30
JA stop
PUSHR ax
PUSHR ax
MUL
OUT
PUSHR ax
PUSH 1
ADD
POP ax
JUMP next
PUSH 1
:stop
ENDING