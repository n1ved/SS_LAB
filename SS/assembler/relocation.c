#include <math.h>
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
  printf("Enter starting address : ");
  scanf("%X",&STARTADDR);
  fscanf(OBJECTCODE,"H^%s",DATA);
  printf("%s\n",DATA);
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
  printf("Program\t%s\nStart\t%X\nLength\t%s\n",NAME,STARTADDR,LENGTH);
  // STARTADDR=atoi(START);
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
  printf("%s\n",DATA);
  // exit(0);
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

    printf("writing %s\n",START);
    // fprintf(MEMORY, "%s\n",START);
    int bytecounter = 0 , curmem = 0;
    char TEMPSTR[7];
    TEMPSTR[6] = '\0';
    curser++;
    while(DATA[curser] != '\0'){
      for(int i=0 ; DATA[curser] != '^' && DATA[curser] != '\0';i++){
        TEMPSTR[i] = DATA[curser];
        printf("%d\n",i);
        curser++;
      }
      printf("%s\n",TEMPSTR);
      curser++;
      fprintf(MEMORY, "%X\t%X\n" , STARTADDR+convert_hex(START)+curmem , convert_hex(TEMPSTR));
      curmem += 3;
    }
    curser = 0;
    fscanf(OBJECTCODE, "%s",DATA);
  }
}
