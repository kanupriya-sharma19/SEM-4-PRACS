#include<stdio.h>
#include<conio.h>

 
int arr[6]={2,-332,4,565,3,-1};
int n=6;
void printArray(int a[], int n){
    int i;
    for(i = 0; i < n; i++){
        printf("%d ", a[i]);
    }
    printf("\n");
}

void selectionSort(int a[], int n){
    int i, j, minIndex, temp;
    for(i = 0; i < n-1; i++){
        minIndex = i;
        for(j = i+1; j < n; j++){
            if(a[j] < a[minIndex]){
                minIndex = j;
            }
        }
        temp = a[i];
        a[i] = a[minIndex];
        a[minIndex] = temp;
    }
}

int main()
{
  
    selectionSort(arr, n);
printArray(arr,n);
    

    return 0;
}