#include<stdio.h>
int frame[3],page[9]={1, 2, 1, 0, 3, 0, 4, 2, 4};
int m=3,n=9;


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

int lru_finder(int idx)
{int min=0,mintime=idx;
    for(int j=0;j<m;j++)
    {
        for(int i=idx-1;i>=0;i--)
        {
            if(frame[j]==page[i])
            {
                if(i<mintime)
                {
                   mintime=i;
                    min=j; 
                }
                break;
            }
        }
    }
    return min;
}

void lru()
{
    int hit=0,miss=0;int count=0;
    for(int i=0;i<m;i++)
    {
        frame[i]=-1;
    }
    for(int i=0;i<n;i++)
    {printf("%d: ",page[i]);
        int find=checker(page[i]);
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
                int replace=lru_finder(i);
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
    }printf("\nHits: %d\nMisses: %d", hit, miss);
}

int main()
{
    lru();
    return 0;
}
