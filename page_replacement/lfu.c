
#include<stdio.h>

int frame[3],page[15]={7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2 };
int m=3,n=15;

int checker(int idx)
{
    for(int j=0;j<m;j++)
    {
        if(frame[j]==idx)
        {
            return 1;
        }
    }
    return -1;
}

int lfufinder(int idx)
{int leastfreq=idx-1;int replace=0;
    for(int j=0;j<m;j++)
    {int framefreq=0;
        for(int i=0;i<idx;i++)
        {
            if(frame[j]==page[i])
            {
                framefreq++;
            }
        }
        if(framefreq<leastfreq)
        {
            replace=j;
            leastfreq=framefreq;
        }
    }
    return replace;
}

void lfu()
{
    int hit=0,miss=0;
    int count=0;
    for(int i=0;i<m;i++)frame[i]=-1;
    for(int i=0;i<n;i++)
    {
        int find=checker(page[i]);
        printf(" %d ",page[i]);
        if(find==1)
        {
            printf(" H ");
            hit++;
        }
        else
        {
            miss++;
            printf(" M ");
            if(count<3)
            {
                frame[count]=page[i];
                count++;
            }
            else
            {
                int replace=lfufinder(i);
                frame[replace]=page[i];
            }
        }
        for(int j=0;j<m;j++)
        {
            if(frame[j]==-1)
            {
                printf(" -- ");
            }
            else
            {
                printf(" %d ",frame[j]);
            }
        }
        printf("\n");
        
    }
     float hitPercent = ((float)hit / n) * 100;
    float faultPercent = ((float)miss / n) * 100;

    printf("\nTotal Page Faults: %d\n", miss);
    printf("Total Hits: %d\n", hit);
    printf("Hit Percent: %.2f%%\n", hitPercent);
    printf("Fault Percent: %.2f%%\n", faultPercent);
}

int main()
{
    lfu();
}