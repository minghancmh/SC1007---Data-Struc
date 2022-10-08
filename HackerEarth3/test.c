#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    int arr[10];
    memset(arr,0,10);
    int n = 0;
    printf("arr is %d\n", arr);


    for (int i=0; i<10; i++){
        arr[i] = 5;
    }


    while (arr[n] != 0){
        printf("%d ", arr[n]);
        n++;
    }






    return 0;
}