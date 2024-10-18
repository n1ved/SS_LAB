#include <stdio.h>
#define MAX_SIZE 3
#define ENDL printf("\n")

int main(){
    int frames[MAX_SIZE] ;
    int frequency[MAX_SIZE];
    int input_size,hit=0,miss=0;
    for(int i=0;i<MAX_SIZE;i++){
        frames[i] = -1;
        frequency[i] = 0;
    }
    printf("Enter string size : ");
    scanf("%d" , &input_size);

    int pages[input_size];


    printf("Enter the string : ");
    for(int i=0 ; i<input_size ;i++){
        scanf("%d" , &pages[i]);
    }

    int input_size_copy = input_size ;

    for(int i=0 ; i<input_size ; i++){
        for(int x=0 ; x<MAX_SIZE ; x++){
            printf("%d ",frames[x]);
        }
        ENDL;
        int found = 0;
        for (int j=0 ; j<MAX_SIZE ; j++){
            if(frames[j] == pages[i]){
                found = 1;
                frequency[j]++;
                hit++;
                break;
            }
        }
        if(found != 1){
            miss++;
            int low = 0;
            for(int k=0 ; k<MAX_SIZE ; k++){
                if(frequency[k] < frequency[low]){
                    low = k;
                }
            }
            frames[low] = pages[i];
            frequency[low] = 1;
        }
    }

    printf("Hit : %d\nMiss : %d\n",hit,miss);

    return 0;
}