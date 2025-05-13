#include <stdio.h>
#include <stdlib.h>

struct Processes {
    int process_id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

void FCFS(struct Processes *process, int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=i+1;j<n;j++) {
            if(process[j].at < process[i].at) {
                struct Processes temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < process[i].at)
            current_time = process[i].at;

        process[i].ct = current_time + process[i].bt;
        current_time = process[i].ct;

        process[i].tat = process[i].ct - process[i].at;
        process[i].wt = process[i].tat - process[i].bt;
    }
}

void printResults(struct Processes *process, int n) {
    float total_tat = 0, total_wt = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (process[i].process_id > process[j].process_id) {
                struct Processes temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", process[i].process_id, process[i].at, process[i].bt, process[i].ct, process[i].tat, process[i].wt);
        total_tat += process[i].tat;
        total_wt += process[i].wt;
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    printf("\nGantt Chart:\n|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", process[i].process_id);
    }
    printf("\n0");
    for (int i = 0; i < n; i++) {
        printf("   %d", process[i].ct);
    }
    printf("\n");
}

int main() {
    int n = 3;
    struct Processes process[3] = {
        {1, 2, 5, 0, 0, 0},
        {2, 0, 3, 0, 0, 0},
        {3, 4, 4, 0, 0, 0},
      
       
    };

    FCFS(process, n);
    printResults(process, n);

    return 0;
}
