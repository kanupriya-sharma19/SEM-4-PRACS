#include <stdio.h>

void LFU(int noPage, int page[], int noFrame, int frame[]) {
    int i, j, hitCount = 0, faultCount = 0;
    int frequency[noFrame];  

    for (i = 0; i < noFrame; i++) {
        frame[i] = -1; 
        frequency[i] = 0; 
    }

    printf("Pages\tFrames\t\tHit\n");

    for (i = 0; i < noPage; i++) {
        int hit = 0;

        for (j = 0; j < noFrame; j++) {
            if (frame[j] == page[i]) {
                hit = 1; 
                hitCount++;
                frequency[j]++; 
                break;
            }
        }

        if (hit == 0) {
            int minFreq = frequency[0];
            int replaceIndex = 0;

            for (j = 1; j < noFrame; j++) {
                if (frequency[j] < minFreq) {
                    minFreq = frequency[j];
                    replaceIndex = j;
                }
            }

            frame[replaceIndex] = page[i];
            frequency[replaceIndex] = 1;
            faultCount++;
        }

        printf("%d\t", page[i]);
        for (j = 0; j < noFrame; j++) {
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

int main() {
    int pages[] = {4, 7, 6, 1, 7, 6, 1, 2, 7, 2};
    int noPages = sizeof(pages) / sizeof(pages[0]);

    int noFrames = 3;
    int frames[noFrames];
    LFU(noPages, pages, noFrames, frames);
    return 0;
}
