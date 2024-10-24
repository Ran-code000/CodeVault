DATA SEGMENT
    STRING DB 'ADRAdfghtGHgff'   
    count equ $-STRING           
DATA ENDS

EXTRA SEGMENT
    DEST DB COUNT DUP (?)        
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
    MOV AH, 4CH                  
    INT 21H                      
CODE ENDS
END BEGIN