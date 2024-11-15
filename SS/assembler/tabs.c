#include<stdio.h>
#include<string.h>

FILE *OBJECTCODE,*MEMORY;

void init(){
    OBJECTCODE=fopen("object.txt","r");
    MEMORY=fopen("mem.txt","w");
}

int convert_hex(char a[]){
    int var=0;
    for(int i=0;i<strlen(a);i++){
        int n=a[i];
        var=var*16+(n<58?n-48:n-55);
    }
    return var;
}

int convert_hexc(char a){
    return a<58?a-48:a-55;
}

int main(){
    init();
    char DATA[100],HEADER[100];
    fscanf(OBJECTCODE,"%s",HEADER);
    fscanf(OBJECTCODE,"T^%s",DATA);
    int cursor=0;
    while(DATA[0]!='E'){
        char START[7],SIZE[3];
        START[6]='\0';
        SIZE[2]='\0';
        cursor+=2;
        for(int i=0;i<6;i++){
            START[i]=DATA[cursor];
            cursor++;
        }
        cursor++;
        for(int i=0;i<2;i++){
            SIZE[i]=DATA[cursor];
            cursor++;
        }
        printf("Writing..\n");
        printf("Text Record:T^%X\n",convert_hex(START));
        printf("Size:%X\n",convert_hex(SIZE));
        fprintf(MEMORY,"%s",START);
        int bytecounter=0;
        while(DATA[cursor]!='\0'){
            if(bytecounter%8==0){
                fprintf(MEMORY,"\t");
                bytecounter=0;
            }
            if(DATA[cursor]!='^'){
                fprintf(MEMORY,"%X",convert_hexc(DATA[cursor]));
                bytecounter++;
            }
            cursor++;
        }
        fprintf(MEMORY,"\n");
        fscanf(OBJECTCODE,"%s",DATA);
        cursor=0;
    }
    fclose(OBJECTCODE);
    fclose(MEMORY);
}
