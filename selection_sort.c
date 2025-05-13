#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void selection_sort(int n, int *arr) {
    for (int i = 0; i < n-1; i++) {
 int min_idx = i;
 for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                              min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
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
    selection_sort(n, arr);
    clock_t time_req2 = clock();
      printf("Elapsed time: %f\n", (float)(time_req2 - time_req1));
      
    printf("Sorted nos elapsed time\n");
    selection_sort(n, arr);
    time_req1 = clock();  
    selection_sort(n, arr);
 time_req2 = clock();
     printf("Elapsed time: %f\n", (float)(time_req2 - time_req1));
     printf("Desc nos elapsed time\n");
     
 selection_sort(n, arr);
 int rev[n], j = 0;  
    for(int i = n-1; i >= 0; i--)  
    {  
        rev[j] = arr[i];  
        j++;  
    }  
     time_req1 = clock();  
    selection_sort(n, rev);
time_req2 = clock();
printf("Elapsed time: %f\n", (float)(time_req2 - time_req1));
   return 0;
}