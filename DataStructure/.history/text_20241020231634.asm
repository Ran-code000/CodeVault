DATA SEGMENT
    STRING DB 'ADRAdfghtGHgff'   ; 源字符串
    count equ $-STRING           ; 计算字符串长度
DATA ENDS

EXTRA SEGMENT
    DEST DB COUNT DUP (?)        ; 目标字符串，大小与源字符串相同
EXTRA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES:EXTRA

BEGIN:
    MOV AX, DATA                 ; 将数据段的起始地址放入AX
    MOV DS, AX                   ; 将数据段地址放入DS寄存器
    MOV AX, EXTRA                ; 将额外段的起始地址放入AX
    MOV ES, AX                   ; 将额外段地址放入ES寄存器
    MOV CX, COUNT                ; 将字符串长度放入CX，作为循环次数
    LEA SI, STRING               ; 将源字符串地址加载到SI寄存器
    LEA DI, DEST                 ; 将目标字符串地址加载到DI寄存器
    CLD                          ; 清除方向标志位，确保字符串操作从低地址向高地址进行
AGAIN:
    LODSB                        ; 从[SI]加载字节到AL寄存器，并自动递增SI
    AND AL, 0DFH                 ; 将字符转换为大写
    STOSB                        ; 将AL中的字符存储到[DI]，并自动递增DI
    LOOP AGAIN                   ; 循环CX次
    MOV AH, 4CH                  ; 系统调用：程序结束
    INT 21H                      ; 中断，返回DOS
CODE ENDS
END BEGIN