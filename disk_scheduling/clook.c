#include <stdio.h>
#include <stdlib.h>

void clook(int movements[], int numMovements, int currentPosition, int direction) {
    int totalSeekTime = 0;
    
    // Sort the requests
    for (int i = 0; i < numMovements - 1; i++) {
        for (int j = i + 1; j < numMovements; j++) {
            if (movements[i] > movements[j]) {
                // Swap
                int temp = movements[i];
                movements[i] = movements[j];
                movements[j] = temp;
            }
        }
    }

    // Start processing the requests
    int i;
    if (direction == 1) {  // Upward direction
        for (i = 0; i < numMovements; i++) {
            if (movements[i] > currentPosition) {
                break;
            }
        }

        // Move upwards to the largest request
        for (int j = i; j < numMovements; j++) {
            totalSeekTime += abs(currentPosition - movements[j]);
            currentPosition = movements[j];
        }

        // After reaching the largest request, jump to the smallest request (0) and move upwards
        totalSeekTime += abs(currentPosition - movements[0]);  // Jump to smallest request
        currentPosition = movements[0];

        // Now service the remaining requests upwards
        for (int j = 1; j < i; j++) {
            totalSeekTime += abs(currentPosition - movements[j]);
            currentPosition = movements[j];
        }
    } else {  // Downward direction
        for (i = numMovements - 1; i >= 0; i--) {
            if (movements[i] < currentPosition) {
                break;
            }
        }

        // Move downwards to the smallest request
        for (int j = i; j >= 0; j--) {
            totalSeekTime += abs(currentPosition - movements[j]);
            currentPosition = movements[j];
        }

        // After reaching the smallest request, jump to the largest request (199) and move downwards
        totalSeekTime += abs(currentPosition - movements[numMovements - 1]);  // Jump to largest request
        currentPosition = movements[numMovements - 1];

        // Now service the remaining requests downwards
        for (int j = numMovements - 2; j > i; j--) {
            totalSeekTime += abs(currentPosition - movements[j]);
            currentPosition = movements[j];
        }
    }

    printf("Total Seek Time: %d\n", totalSeekTime);
}

int main() {
    int movements[] = {82, 170, 43, 140, 24, 16, 190};
    int numMovements = 7;
    int currentPosition = 50;
    int direction = 1;  // 1 for upwards, 0 for downwards

    clook(movements, numMovements, currentPosition, direction);

    return 0;
}
