#include <stdio.h>
#define MAX_SIZE 3
#define ENDL printf("\n")

int main(){
    int frames[MAX_SIZE] ;
    int recency[MAX_SIZE];
    int input_size,hit=0,miss=0;
    for(int i=0;i<MAX_SIZE;i++){
        frames[i] = -1;
        recency[i] = 0;
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
        // for(int x=0 ; x<MAX_SIZE ; x++){
        //     printf("%d ",frames[x]);
        // }
        // ENDL;
        int found = 0;
        for(int k=0 ; k<MAX_SIZE ; k++)
            recency[k]++;
        for (int j=0 ; j<MAX_SIZE ; j++){
            if(frames[j] == pages[i]){
                found = 1;
                recency[j] = 0;
                hit++;
                break;
            }
        }
        if(found != 1){
            miss++;
            int high = 0;
            for(int k=0 ; k<MAX_SIZE ; k++){
                if(recency[k] > recency[high]){
                    high = k;
                }
            }
            frames[high] = pages[i];
            recency[high] = 0;
        }
    }

    printf("Hit : %d\nMiss : %d\n",hit,miss);

    return 0;
}
