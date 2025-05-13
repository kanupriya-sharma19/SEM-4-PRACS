#include <stdio.h>

#define TIME_QUANTUM 3 // Define the time quantum

struct Processes {
    int process_id;
    int at; // Arrival Time
    int bt; // Burst Time
    int remaining_bt; // Remaining Burst Time
    int ct; // Completion Time
    int tat; // Turnaround Time
    int wt; // Waiting Time
};

void RoundRobin(struct Processes *process, int n) {
    int current_time = 0;
    int remaining_time[n];

    // Initialize remaining burst time for all processes
    for (int i = 0; i < n; i++) {
        remaining_time[i] = process[i].bt;
    }

    while (1) {
        int done = 1;

        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0; // There are still processes left to execute

                // Process runs for a time slice
                if (remaining_time[i] > TIME_QUANTUM) {
                    current_time += TIME_QUANTUM;
                    remaining_time[i] -= TIME_QUANTUM;
                }
                else {
                    // Process finishes in the current time slice
                    current_time += remaining_time[i];
                    process[i].ct = current_time;
                    remaining_time[i] = 0;
                }
            }
        }

        // If all processes are done, break the loop
        if (done == 1) {
            break;
        }
    }

    // Calculate TAT and WT after all processes are completed
    for (int i = 0; i < n; i++) {
        process[i].tat = process[i].ct - process[i].at; // Turnaround time
        process[i].wt = process[i].tat - process[i].bt; // Waiting time
    }
}

void printResults(struct Processes *process, int n) {
    float total_tat = 0, total_wt = 0;

    // Print the table with process details
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

    // Gantt Chart
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
        {2, 1, 4, 0, 0, 0, 0},
        {3, 2, 2, 0, 0, 0, 0},
        {4, 4, 1, 0, 0, 0, 0}
    };

    RoundRobin(process, n);
    printResults(process, n);

    return 0;
}
