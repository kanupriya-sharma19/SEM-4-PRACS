#include <stdio.h>

void LFU(int noPage, int page[], int noFrame, int frame[]) {
    int i, j, hitCount = 0, faultCount = 0;
    int frequency[noFrame];  // To track the frequency of pages in the frame

    // Initialize the frames and frequencies
    for (i = 0; i < noFrame; i++) {
        frame[i] = -1; // Initially no pages in the frame
        frequency[i] = 0; // Frequency of all pages is 0 initially
    }

    printf("Pages\tFrames\t\tHit\n");

    // Process each page
    for (i = 0; i < noPage; i++) {
        int hit = 0;

        // Check for a hit in the frame
        for (j = 0; j < noFrame; j++) {
            if (frame[j] == page[i]) {
                hit = 1; // Page is already in the frame
                hitCount++;
                frequency[j]++; // Increase the frequency of the accessed page
                break;
            }
        }

        // If it's a page fault, replace the least frequently used page
        if (hit == 0) {
            // Find the page with the least frequency
            int minFreq = frequency[0];
            int replaceIndex = 0;

            for (j = 1; j < noFrame; j++) {
                if (frequency[j] < minFreq) {
                    minFreq = frequency[j];
                    replaceIndex = j;
                }
            }

            // Replace the page at replaceIndex with the new page
            frame[replaceIndex] = page[i];
            frequency[replaceIndex] = 1; // Set frequency of the newly added page to 1
            faultCount++;
        }

        // Print current state
        printf("%d\t", page[i]);
        for (j = 0; j < noFrame; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\t\t%d\n", hit);
    }

    // Print statistics
    float hitPercent = ((float)hitCount / noPage) * 100;
    float faultPercent = ((float)faultCount / noPage) * 100;

    printf("Page Faults: %d\n", faultCount);
    printf("Hits: %d\n", hitCount);
    printf("Hit Percent: %.2f%%\n", hitPercent);
    printf("Fault Percent: %.2f%%\n", faultPercent);
}

int main() {
    int pages[] = {2, 3, 4, 2, 1, 3, 7, 5, 4, 3};
    int noPages = sizeof(pages) / sizeof(pages[0]);

    int noFrames = 3;
    int frames[noFrames];
    LFU(noPages, pages, noFrames, frames);
    return 0;
}
