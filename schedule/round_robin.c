#include <stdio.h>
#include <stdbool.h>
#define MAX 1000

int g[MAX], gt[MAX], gi = 0; 

struct Processes {
    int process_id;
    int at; 
    int bt; 
    int remaining_bt; 
    int ct;
    int tat; 
    int wt; 
};

void RoundRobin(struct Processes *process, int n, int tq) {
    int current_time = 0;
    int completed = 0;
    bool executed[MAX] = {false};

    for (int i = 0; i < n; i++) {
        process[i].remaining_bt = process[i].bt;
    }

    while (completed < n) {
        bool all_executed = true;
        
        for (int i = 0; i < n; i++) {
            if (process[i].at <= current_time && process[i].remaining_bt > 0) {
                all_executed = false; 
                
                int exec_time = (process[i].remaining_bt > tq) ? tq : process[i].remaining_bt;

                for (int t = 0; t < exec_time; t++) {
                    g[gi] = process[i].process_id;
                    gt[gi] = current_time + 1;
                    gi++;
                    current_time++;
                }

                process[i].remaining_bt -= exec_time;

                if (process[i].remaining_bt == 0) {
                    process[i].ct = current_time;
                    process[i].tat = process[i].ct - process[i].at;
                    process[i].wt = process[i].tat - process[i].bt;
                    completed++;
                }
            }
        }

        if (all_executed) {
            current_time++;
        }
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
    int n = 6;
    int tq = 4;

    struct Processes process[6] = {
        {0, 0, 5, 0, 0, 0, 0},  
        {1, 1, 6, 0, 0, 0, 0},
        {2, 2, 3, 0, 0, 0, 0},
        {3, 3, 1, 0, 0, 0, 0},
        {4, 4, 5, 0, 0, 0, 0},
        {5, 5, 4, 0, 0, 0, 0}
    };

    RoundRobin(process, n, tq);
    printResults(process, n);

    return 0;
}
