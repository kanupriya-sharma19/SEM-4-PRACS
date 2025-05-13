#include<stdio.h>
#include<stdlib.h>

#define MAX 1000

struct pro
{
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rem;
};

int g[MAX], gt[MAX], gi = 0; 
struct pro pro[6];
int n;

int front = -1, rear = -1;
int size = 6;
int q[6];

void enqueue(int val)
{
    if (((rear + 1) % size) == front)
    {
        return;
    }
    else if (front == -1)
    {
        front = rear = 0;
        q[rear] = val;
    }
    else
    {
        rear = (rear + 1) % size;
        q[rear] = val;
    }
}

int dequeue()
{
    if (front == -1)
    {
        return -1;
    }
    int val = q[front];
    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front = (front + 1) % size;
    }
    return val;
}

void rr(int quant)
{
    int current_time = 0;
    int count = 0;
    int visited[100] = {0};
    int prev = -1;

    while (count < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (pro[i].at <= current_time && pro[i].rem > 0 && visited[i] == 0)
            {
                enqueue(i);
                visited[i] = 1;
            }
        }

        if (prev != -1)
        {
            enqueue(prev);
        }

        if (front == -1 && count < n)
        {
            for (int i = 0; i < n; i++)
            {
                if (pro[i].rem > 0)
                {
                    current_time = pro[i].at;
                    enqueue(i);
                    break;
                }
            }
        }

        int val = dequeue();
        if (val == -1) break;

        int executed = (pro[val].rem > quant) ? quant : pro[val].rem;

        for (int i = 0; i < executed; i++)
        {
            g[gi] = val;
            current_time++;
            gt[gi] = current_time;
            gi++;
        }

        pro[val].rem -= executed;

        if (pro[val].rem == 0)
        {
            count++;
            pro[val].ct = current_time;
            pro[val].tat = pro[val].ct - pro[val].at;
            pro[val].wt = pro[val].tat - pro[val].bt;
            prev = -1;
        }
        else
        {
            prev = val;
        }
    }
}

void display()
{
      
    float tat1 = 0, wt1 = 0;
    printf("P\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i, pro[i].at, pro[i].bt, pro[i].ct, pro[i].tat, pro[i].wt);
        tat1 += pro[i].tat;
        wt1 += pro[i].wt;
    }

    tat1 /= n;
    wt1 /= n;
    printf("Avg TAT: %.2f\nAvg WT: %.2f\n", tat1, wt1);

    printf("\nDetailed Gantt Chart (every second):\n");
    for (int i = 0; i < gi; i++) printf("|P%d", g[i]);
    printf("|\n");

    printf("0");
    for (int i = 0; i < gi; i++) printf("  %d", gt[i]);
    printf("\n");
}

int main()
{
    n = 3;
    int tq = 2;

    pro[0] = (struct pro){0, 4, 0, 0, 0, 4};
    pro[1] = (struct pro){0, 5, 0, 0, 0, 5};
    pro[2] = (struct pro){0, 3, 0, 0, 0, 3};
   

    rr(tq);
    display();
    return 0;
}
