DATA SEGMENT
  NUM1 DB 52
  NUM2 DB 31
  NUM3 DB ?
DATA ENDS
CODE SEGMENT
  ASSUME CS:CODE,DS:DATA
  START:
    MOV AX,DATA
    MOV DS,AX
    MOV AL,NUM1
    MOV BL,NUM2
    ADD AL,BL
    AAM
    MOV BX,AX
    MOV DL,AH
    ADD DL,30H
    MOV AH,02H
    INT 21H
    MOV AL,BL
    MOV DL,AL
    ADD DL,30H
    MOV AH,02H
    INT 21H
CODE ENDS
END START
