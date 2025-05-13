#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int n, int *arr) {
     for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (key < arr[j] && j >= 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}
int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
   

    srand(time(NULL)); 
    for (int i = 0; i < n; i++) {
        arr[i] = rand() ;
    }
    printf("Random nos elapsed time\n");
    clock_t time_req1 = clock();  
    insertion_sort(n, arr);
    clock_t time_req2 = clock();
      printf("Elapsed time: %f\n", (float)(time_req2 - time_req1));
      
    printf("Sorted nos elapsed time\n");
    insertion_sort(n, arr);
    time_req1 = clock();  
    insertion_sort(n, arr);
 time_req2 = clock();
     printf("Elapsed time: %f\n", (float)(time_req2 - time_req1));
     printf("Desc nos elapsed time\n");
     
 insertion_sort(n, arr);
 int rev[n], j = 0;  
    for(int i = n-1; i >= 0; i--)  
    {  
        rev[j] = arr[i];  
        j++;  
    }  
     time_req1 = clock();  
    s_sort(n, rev);
time_req2 = clock();
printf("Elapsed time: %f\n", (float)(time_req2 - time_req1));
   return 0;
}