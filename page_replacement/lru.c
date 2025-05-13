#include <stdio.h>

int findLRU(int time[], int noFrame)
{
    int i, min = time[0], index = 0;
    for (i = 1; i < noFrame; i++)
    {
        if (time[i] < min)
        {
            min = time[i];
            index = i;
        }
    }
    return index;
}

void LRU(int noPage, int page[], int noFrame, int frame[])
{
    int i, j, hitCount = 0, faultCount = 0;
    int time[noFrame]; // To track usage time
    int counter = 0;

    for (i = 0; i < noFrame; i++)
    {
        frame[i] = -1;
        time[i] = 0;
    }

    printf("Pages\tFrames\t\tHit\n");

    for (i = 0; i < noPage; i++)
    {
        int hit = 0;

        for (j = 0; j < noFrame; j++)
        {
            if (frame[j] == page[i])
            {
                counter++;
                time[j] = counter;
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
                counter++;
                time[faultCount] = counter;
            }
            else
            {
                int indexToReplace = findLRU(time, noFrame);
                frame[indexToReplace] = page[i];
                counter++;
                time[indexToReplace] = counter;
            }
            faultCount++;
        }

        // Print current state
        printf("%d\t", page[i]);
        for (j = 0; j < noFrame; j++)
        {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\t\t%d\n", hit);
    }

    float hitPercent = ((float)hitCount / noPage) * 100;
    float faultPercent = ((float)faultCount / noPage) * 100;

    printf("Page Faults: %d\n", faultCount);
    printf("Hits: %d\n", hitCount);
    printf("Hit Percent: %.2f%%\n", hitPercent);
    printf("Fault Percent: %.2f%%\n", faultPercent);
}
int main()
{
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int noPages = sizeof(pages) / sizeof(pages[0]);

    int noFrames = 4;
    int frames[noFrames];
    LRU(noPages, pages, noFrames, frames);
    return 0;
}
