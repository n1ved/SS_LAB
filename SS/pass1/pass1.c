#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FILE *SOURCE , *OPTAB , *SYMTAB ,*SYMCH, *INTERMIDIATE , *LENGTH;
char OPCODE[20],CODE[20],HEX[20],LABEL[20],OPERAND[20];
unsigned int LOCCTR;

void initf(){
  SOURCE = fopen("source.txt", "r");
  OPTAB = fopen("optab.txt", "r");
  SYMCH = fopen("symtab.txt", "r");

  SYMTAB = fopen("symtab.txt", "w");
  INTERMIDIATE = fopen("intermediate.txt", "w");
  LENGTH = fopen("length.txt", "w");
}

void write_symtab(char label[] , char hex[]){
  fprintf(SYMTAB, "%s\t%s\n",label,hex);
}

int main(){
  initf();
  fscanf(SOURCE, "%s\t%s\t%s",LABEL,OPCODE,OPERAND);
  if(strcmp(OPCODE, "START") == 0){
    printf("found START\n");
    fseek(SOURCE, SEEK_SET, 0);
    fscanf(SOURCE, "%s\t%s\t%X",LABEL,OPCODE,&LOCCTR);
    fprintf(INTERMIDIATE, "**\t%s\t%s\t%s\n",LABEL,OPCODE,OPERAND);
    fscanf(SOURCE, "%s\t%s\t%s", LABEL,OPCODE,OPERAND);
  }else{
    LOCCTR = 0;
  }

  while(strcmp(OPCODE,  "END") != 0){
    fprintf(INTERMIDIATE, "%X\t",LOCCTR);
    if(strcmp(LABEL, "**") !=0){
      fseek(SYMCH, SEEK_SET, 0);
      fscanf(SYMCH, "%s\t%s",CODE,HEX);
      while(!feof(SYMCH)){
        if(strcmp(CODE, LABEL) == 0){
          printf("E : Duplicate symbol\n");
          exit(-1);
        }
        fscanf(SYMCH, "%s\t%s",CODE,HEX);
      }
      write_symtab(LABEL, OPERAND);
    }
    fseek(OPTAB, SEEK_SET, 0);
    fscanf(OPTAB,"%s\t%s",CODE,HEX);
    bool found = false;
    while(strcmp(CODE, "END") != 0){
      if(strcmp(OPCODE, CODE) == 0){
        found = true;
        break;
      }
      fscanf(OPTAB, "%s\t%s",CODE,HEX);
    }
    if(found){
      LOCCTR += 3;
    }else if (strcmp(OPCODE, "BYTE")) {
      LOCCTR += 1;
    }else if (strcmp(OPCODE, "WORD")) {
      LOCCTR += 3;
    }else if (strcmp(OPCODE, "RESW")) {
      LOCCTR += 3*atoi(OPERAND);
    }else if (strcmp(OPCODE, "RESB")) {
      LOCCTR += atoi(OPERAND);
    }else{
      printf("E : Unknown opcode\n");
      exit(-2);
    }
    fprintf(INTERMIDIATE, "%s\t%s\t%s\n",LABEL,OPCODE,OPERAND);
    fscanf(SOURCE, "%s\t%s\t%s", LABEL,OPCODE,OPERAND);
  }
  fprintf(INTERMIDIATE, "%X\t%s\t%s\t%s",LOCCTR,LABEL,OPCODE,OPERAND);

  return 0;
}
