PUSH 1
POP ax
:next
PUUSH ax
PUSH 30
JA stop
PUUSH ax
PUUSH ax
MUL
OUT
PUUSH ax
PUSH 1
ADD
POP ax
JUMP next
PUSH 1
:stop
ENDING