#include <stdio.h>
#include <stdbool.h>

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

    // Initialize remaining burst time for preemptive scheduling
    for (int i = 0; i < n; i++) {
        process[i].remaining_bt = process[i].bt;
    }

    while (completed < n) {
        int min_bt = 1e9;
        
        // Find the process with the shortest remaining burst time
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
        
        // If no process is available to execute, increment current time
        if (idx == -1) {
            current_time++;
            continue;
        }

        // Execute the process by reducing the remaining burst time
        process[idx].remaining_bt--;
        
        // If the process completes, calculate its completion time, turnaround time, and waiting time
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
    // Sorting processes by process_id to display in P1, P2, P3, P4 order
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (process[i].process_id > process[j].process_id) {
                struct Processes temp = process[i];
                process[i] = process[j];
                process[j] = temp;
            }
        }
    }

    float total_tat = 0, total_wt = 0;

    // Print the table with process details in the correct order
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

    // Optional Gantt Chart
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
