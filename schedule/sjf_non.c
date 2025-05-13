#include <stdio.h>
#include <stdbool.h>

struct Processes {
    int process_id;
    int at; 
    int bt; 
    int ct; 
    int tat; 
    int wt; 
};

void SJF_NonPreemptive(struct Processes *process, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (process[i].at > process[j].at) {
                struct Processes temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    int current_time = process[0].at;

    for (int i = 0; i < n; i++) {
        if (current_time < process[i].at) {
            current_time = process[i].at; 
        }

        int shortest = i;
        for (int j = i + 1; j < n; j++) {
            if (process[j].at <= current_time && process[j].bt < process[shortest].bt) {
                shortest = j;
            }
        }

        struct Processes temp = process[i];
        process[i] = process[shortest];
        process[shortest] = temp;

        process[i].ct = current_time + process[i].bt;
        process[i].tat = process[i].ct - process[i].at;
        process[i].wt = process[i].tat - process[i].bt;

        current_time = process[i].ct;
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
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               process[i].process_id,
               process[i].at,
               process[i].bt,
               process[i].ct,
               process[i].tat,
               process[i].wt);
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

    int last_ct = 0;
    for (int i = 0; i < n; i++) {
        printf("   %d", process[i].ct);
        last_ct = process[i].ct;
    }
    printf("\n");
}

int main() {
    int n = 5;
    struct Processes process[5] = {
        {1, 2, 6, 0, 0, 0},
        {2, 5, 2, 0, 0, 0},
        {3, 1, 8, 0, 0, 0},
        {4, 0, 3, 0, 0, 0},
          {5, 4, 4, 0, 0, 0}
    };

    SJF_NonPreemptive(process, n);
    printResults(process, n);

    return 0;
}
