#include <stdio.h>

void scan(int movements[], int numMovements, int currentPosition, int direction) {
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

        // Move upwards to the end (199)
        for (int j = i; j < numMovements; j++) {
            totalSeekTime += abs(currentPosition - movements[j]);
            currentPosition = movements[j];
        }

        // After reaching the end, move to the lowest (0)
        totalSeekTime += abs(currentPosition - 199);  // Move to 199
        currentPosition = 199;

        // Now move downwards
        for (int j = i - 1; j >= 0; j--) {
            totalSeekTime += abs(currentPosition - movements[j]);
            currentPosition = movements[j];
        }
    } else {  // Downward direction
        for (i = numMovements - 1; i >= 0; i--) {
            if (movements[i] < currentPosition) {
                break;
            }
        }

        // Move downwards to the start (0)
        for (int j = i; j >= 0; j--) {
            totalSeekTime += abs(currentPosition - movements[j]);
            currentPosition = movements[j];
        }

        // After reaching 0, move to the highest (199)
        totalSeekTime += abs(currentPosition - 0);  // Move to 0
        currentPosition = 0;

        // Now move upwards
        for (int j = i + 1; j < numMovements; j++) {
            totalSeekTime += abs(currentPosition - movements[j]);
            currentPosition = movements[j];
        }
    }

    printf("Total Seek Time: %d\n", totalSeekTime);
}

int main() {
    int movements[] = {82,170,43,140,25,16,190};
    int numMovements = 7;
    int currentPosition = 50;
    int direction = 1;  // 1 for upwards, 0 for downwards

    scan(movements, numMovements, currentPosition, direction);

    return 0;
}
