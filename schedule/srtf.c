#include <stdio.h>
#include <stdbool.h>
#define MAX 1000
int g[MAX], gt[MAX], gi = 0; // Process IDs and corresponding time units

struct Processes {
    int process_id;
    int at; // Arrival Time
    int bt; // Burst Time
    int remaining_bt; // Remaining Burst Time (for preemptive version)
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
};

void SJF_Preemptive(struct Processes *process, int n) {
    int current_time = 0;
    int completed = 0;
    int idx = -1;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (process[i].at > process[j].at) {
                struct Processes temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        process[i].remaining_bt = process[i].bt;
    }

    while (completed < n) {
        int min_bt = 1e9;
        
        for (int i = 0; i < n; i++) {
            if (process[i].at <= current_time && process[i].remaining_bt > 0) {
                if (process[i].remaining_bt < min_bt) {
                    min_bt = process[i].remaining_bt;
                    idx = i;
                } else if (process[i].remaining_bt == min_bt && process[i].at < process[idx].at) {
                    idx = i;
                }
            }
        }
        
        if (idx == -1) {
            current_time++;
            continue;
        }

        g[gi] = process[idx].process_id;
gt[gi] = current_time + 1;
gi++;

process[idx].remaining_bt--;
        
        if (process[idx].remaining_bt == 0) {
            process[idx].ct = current_time + 1;
            process[idx].tat = process[idx].ct - process[idx].at;
            process[idx].wt = process[idx].tat - process[idx].bt;
            completed++;
        }
        
        current_time++;
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
printf("\nDetailed Gantt Chart (every second):\n");

for (int i = 0; i < gi; i++) {
    printf("|P%d", g[i]);
}
printf("|\n");

printf("0");
for (int i = 0; i < gi; i++) {
    printf("  %d", gt[i]);
}
printf("\n");


}

int main() {
    int n = 4;
    struct Processes process[4] = {
        {1, 0, 5, 0, 0, 0, 0},  // {Process ID, Arrival Time, Burst Time, Completion Time, Turnaround Time, Waiting Time}
        {2, 1, 3, 0, 0, 0, 0},
        {3, 2, 4, 0, 0, 0, 0},
        {4, 4, 1, 0, 0, 0, 0}
    };

    SJF_Preemptive(process, n);
    printResults(process, n);

    return 0;
}
