DATA SEGMENT
    STRING DB 'ADRAdfghtGHgff'   
    COUNT  EQU $ - STRING           
DATA ENDS

EXTRA SEGMENT
    DEST DB COUNT DUP (?), '$'   ; 添加结束符
EXTRA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA, ES:EXTRA

BEGIN:
    MOV AX, DATA                
    MOV DS, AX                   
    MOV AX, EXTRA               
    MOV ES, AX                   
    MOV CX, COUNT               
    LEA SI, STRING               
    LEA DI, DEST                 
    CLD                         

AGAIN:
    LODSB                        
    AND AL, 0DFH                 
    STOSB                       
    LOOP AGAIN                   

    MOV DX, OFFSET DEST          ; 将目标字符串地址放入 DX
    MOV AH, 09H                  ; DOS 打印字符串功能
    INT 21H                      ; 调用中断，输出字符串

    MOV AH, 4CH                  ; 结束程序
    INT 21H                      ; 中断返回 DOS
CODE ENDS
END BEGIN