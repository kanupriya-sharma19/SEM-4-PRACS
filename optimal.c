#include <stdio.h>

int findFarthest(int page[], int frame[], int noPage, int noFrame, int currentIndex)
{
    int i, j, farthest = currentIndex, indexToReplace = -1;

    for (i = 0; i < noFrame; i++)
    {
        int found = 0;
        for (j = currentIndex; j < noPage; j++)
        {
            if (frame[i] == page[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    indexToReplace = i;
                }
                found = 1;
                break;
            }
        }
        if (found == 0)
        {
            // This frame's page is never used again
            return i;
        }
    }

    if (indexToReplace == -1)
        return 0;
    else
        return indexToReplace;
}

void Optimal(int noPage, int page[], int noFrame, int frame[])
{
    int i, j, hitCount = 0, faultCount = 0;

    // Initialize all frames to -1
    for (i = 0; i < noFrame; i++)
    {
        frame[i] = -1;
    }

    printf("Pages\tFrames\t\tHit\n");

    // inside Optimal()
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
        // Page fault occurred
        if (faultCount < noFrame)
        {
            frame[faultCount] = page[i];
        }
        else
        {
            int indexToReplace = findFarthest(page, frame, noPage, noFrame, i + 1);
            frame[indexToReplace] = page[i];
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
    int pages[] = {7,0,1,2,0,3,0,4,2,3,0,3,2,1,2,0,1,7,0,1};
    int noPages = sizeof(pages) / sizeof(pages[0]);
    int noFrames = 4;
    int frames[noFrames];

    Optimal(noPages, pages, noFrames, frames);

    return 0;
}
