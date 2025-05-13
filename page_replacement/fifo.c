#include <stdio.h>


void Optimal(int noPage, int page[], int noFrame, int frame[])
{
    int i, j, hitCount = 0, faultCount = 0,framehead=0;

    for (i = 0; i < noFrame; i++)
    {
        frame[i] = -1;
    }

    printf("Pages\tFrames\t\tHit\n");

for (i = 0; i < noPage; i++)
{
    int hit = 0;
    for (j = 0; j < noFrame; j++)
    {
        if (frame[j] == page[i])
        {
            hit = 1;
            hitCount++;
            break;
        }
    }

    if (hit == 0)
    {
        if (faultCount < noFrame)
        {
            frame[faultCount] = page[i];
        }
        else
        {
            
            frame[framehead] = page[i];
            framehead=(framehead+1)%noFrame;
        }
        faultCount++;
    }

    printf("%d \t", page[i]);
    for (j = 0; j < noFrame; j++)
    {
        printf("%d ", frame[j]);
    }
    printf("\t %d\n", hit);
}


    float hitPercent = ((float)hitCount / noPage) * 100;
    float faultPercent = ((float)faultCount / noPage) * 100;

    printf("\nTotal Page Faults: %d\n", faultCount);
    printf("Total Hits: %d\n", hitCount);
    printf("Hit Percent: %.2f%%\n", hitPercent);
    printf("Fault Percent: %.2f%%\n", faultPercent);
}

int main()
{
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2};
    int noPages = sizeof(pages) / sizeof(pages[0]);
    int noFrames = 3;
    int frames[noFrames];

    Optimal(noPages, pages, noFrames, frames);

    return 0;
}
