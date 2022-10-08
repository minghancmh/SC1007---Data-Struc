#include <stdio.h>
#include <stdlib.h>

//the random function generates the same series of numbers on every run!

int main(){
    for (int n=0; n<10; n++){
        for (int i=0; i<10; i++){
            printf("%d ", rand()%2);
        }
        printf("\n");

    }
    
    return 0;
}

