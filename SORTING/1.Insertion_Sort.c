#include <stdio.h>

int arr[9]={2,-332,4,565,3,-1,-324,32432,32};
int n=9;
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {   
        j = i;
        while (j >0 && arr[j-1] >arr[j]) {
         int t=arr[j-1];
         arr[j-1]=arr[j];
         arr[j]=t;
         j--;
        }
        
    }
}

void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    
  

    insertionSort(arr, n);
printArray(arr,n);
    

    return 0;
}
