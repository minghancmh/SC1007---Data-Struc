#include <stdio.h>
#include <stdlib.h>

int min(int arr[]);

int main(){

    int arr1[12] = {5,6,7,8,9,10,11,12,1,2,3,4};
    int arr2[12] = {10,11,12,1,2,3,4,5,6,7,8,9};
    int arr3[5] = {4,5,1,2,3};
    int arr4[4] = {3,4,1,2};
    int arr5[4] = {4,1,2,3};
    int arr6[4] = {1,2,3,4};

    printf("min of arr4 is %d\n", min(arr6));
    // printf("min of arr5 is %d\n", min(arr2));
    // printf("min of arr6 is %d\n", min(arr3));

    return 0;
}

int min(int arr[]){
    int l=0;

    // while(arr[l]!=NULL){
    //     printf("current element in arr is %d\n", arr[l]);
    //     l++;
    // }
    l = sizeof(arr)/sizeof(int);

    return l;

    

}