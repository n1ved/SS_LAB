#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int main(){
    int start,locctr,length;
    char opcode[10] , label[10] , operand[10], hex[10] , code[10];
    FILE *source,*intermediate,*symtab,*optab,*symcheck;
    source = fopen("source.temp.txt", "r");
    intermediate = fopen("intermediate.temp.txt","w");
    symtab = fopen( "symtab.temp.txt", "w");
    optab = fopen("optab.temp.txt", "r");
    symcheck = fopen("symtab.temp.txt", "r");


    fscanf(source,"%s\t%s\t%s", label,opcode,operand);
    if(strcmp(opcode, "START") == 0){
        start = atoi(operand);
        locctr = start;
        fprintf(intermediate , "*\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(source, "%s\t%s\t%s", label,opcode,operand);
    }else{
        locctr = 0;
    }

    while(strcmp(opcode, "END")!=0){
        if(strcmp(label, "#") == 0){
            continue;
        }
        printf("%s\t%s\t%s\n",label,opcode,operand);
        fprintf(intermediate, "%d\t",locctr);
        if(strcmp(label, "*") != 0){
            char loc[10];
            fseek(symcheck, SEEK_SET, 0);
            fscanf(symcheck,"%s\t%s", code,loc);
            while(!feof(symcheck)){
                if(strcmp(code, label) == 0){
                    printf("Error : Duplicate Symbol\n");
                    return -1;
                }
                fscanf(symcheck,"%s\t%s", code,loc);
            }
            fprintf(symtab, "%s\t%d\n" , label,locctr);
        }
        fseek(optab, SEEK_SET, 0);
        fscanf(optab, "%s\t%s",code,hex);
        bool isFound = false;
        while(strcmp(code, "END") != 0){
            if(strcmp(code,opcode) == 0){
                locctr += 3;
                isFound = true;
                break;
            }
            fscanf(optab, "%s\t%s" ,code,hex);
        }
        if(!isFound){
            if(strcmp(opcode  , "WORD") == 0){
                locctr += 3;
            }else if(strcmp(opcode  , "RESW") == 0){
                locctr += 3*atoi(operand);
            }else if(strcmp(opcode, "BYTE") == 0){
                locctr += 1;
            }else if(strcmp(opcode, "RESB") == 0){
                locctr += atoi(operand);
            }else{
                printf("Error : Invalid OPCODE %s\n",opcode);
                return -2;
            }
        }
        fprintf(intermediate, "%s\t%s\t%s\n",label,opcode,operand);
        fscanf(source, "%s\t%s\t%s",label,opcode,operand);
    }
    fprintf(intermediate, "*\t%s\t%s\t%s", label,opcode,operand);
    fclose(source);
    fclose(intermediate);
    fclose(optab);
    fclose(symtab);
    return 0;
}
