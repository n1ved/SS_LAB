DATA SEGMENT
       MSG1 DB 10,13,'Enter ffs : $'
       MSG2 DB 10,13,'P$'
       MSG3 DB 10,13,'N$'
       STR DB 50 DUP(?)
DATA ENDS
CODE SEGNEMT
    ASSUME CS:CODE,DS:DATA
    START:
        MOV AX,DATA
        MOV DS,AX
        
        LEA DX.MSG1
        MOV AH,09H
        INT 21H
        
        LEA SI,STR
        LEA DI,STR
        
    INPUT:
        MOV AH,01H
        INT 21H
        CMP AL,13
        JE TERM
        MOV [DI],AL
        INC DI
        JMP INPUT
    TERM:
        MOV AL,'$'
        MOV [DI],AL
        DEC DI
        MOV BX,DI
    CHECK:
        MOV AL,[SI]
        CMP AL,[DI]
        JNE NP
        INC SI
        DEC DI
        CMP SI,DI
        JL CHECK
    P:         
        LEA DX,MSG2
        MOV AH,09H
        INT 21H
        JMP ENDPRGRM
    N:
        LEA DX,MSG3
        MOV AH,09H
        INT 21H
    ENDPRGRM:
        MOV AH,4CH
        INT 21H
CODE ENDS
END START                        