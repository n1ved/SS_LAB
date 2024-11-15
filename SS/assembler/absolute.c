#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *OBJECTCODE , *MEMORY;
int STARTADDR;

void init(){
  OBJECTCODE = fopen("object.txt","r");
  MEMORY = fopen("memfile.txt", "w");
}

void read_header(){
  char DATA[30],NAME[10],START[7],LENGTH[7];
  int i;
  fscanf(OBJECTCODE,"H^%s",DATA);
  for(i=0 ; DATA[i] != '^' ; i++){
    NAME[i] = DATA[i];
  }
  NAME[i] = '\0';
  START[6] ='\0';
  LENGTH[6] = '\0';
  i++;
  for(int j=0 ; j<6 ; j++){
    START[j] = DATA[i];
    i++;
  }
  i++;
  for(int j=0 ; j<6 ; j++){
    LENGTH[j] = DATA[i];
    i++;
  }
  printf("Program\t%s\nStart\t%s\nLength\t%s\n",NAME,START,LENGTH);
  STARTADDR=atoi(START);
  return;
}

int convert_hex(char a[]){
	int var = 0;
	for(int i=0 ; i<strlen(a) ; i++){
		int n = a[i];
		var = var*16 + ( n<58 ? n-48 : n-55 );
	}
	return  var;
}

int convert_hexc(char a){
  return  a<58 ? a-48 : a-55;
}

int main(){
  char DATA[100];
  int curser = 0;
  init();
  read_header();
  fscanf(OBJECTCODE, "%s",DATA);
  while(DATA[0] != 'E'){
    char START[7],SIZE[3];
    START[6] = '\0';
    SIZE[2] = '\0';
    curser += 2 ; //SKIP T^
    for(int i=0 ; i<6 ; i++){
      START[i] = DATA[curser];
      curser++;
    }
    printf("Text record found at %s\n", START);
    curser++;
    for(int i=0 ; i<2 ;i++){
      SIZE[i] = DATA[curser];
      curser++;
    }
    printf("Size of text record %X\n", convert_hex(SIZE));

    printf("writing...record%s\n",START);
    fprintf(MEMORY, "%s",START);
    int bytecounter = 0 ;
    while(DATA[curser] != '\0'){
      if(bytecounter%8 == 0){
        fprintf(MEMORY, "\t");
        bytecounter = 0;
      }
      if(DATA[curser] != '^'){
        fprintf(MEMORY, "%c",DATA[curser]);
        bytecounter++;
      }
      curser++;
    }
    fprintf(MEMORY, "\n");
    fscanf(OBJECTCODE, "%s",DATA);
    curser = 0;
  }
}
