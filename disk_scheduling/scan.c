#include <stdio.h>

void scan(int movements[], int numMovements, int currentPosition, int direction) {
    int totalSeekTime = 0;
    
    for (int i = 0; i < numMovements - 1; i++) {
        for (int j = i + 1; j < numMovements; j++) {
            if (movements[i] > movements[j]) {
                int temp = movements[i];
                movements[i] = movements[j];
                movements[j] = temp;
            }
        }
    }

    int i;
    if (direction == 1) {  
        for (i = 0; i < numMovements; i++) {
            if (movements[i] > currentPosition) {
                break;
            }
        }

        for (int j = i; j < numMovements; j++) {
            totalSeekTime += abs(currentPosition - movements[j]);
            currentPosition = movements[j];
        }

        totalSeekTime += abs(currentPosition - 199);  
        currentPosition = 199;

        for (int j = i - 1; j >= 0; j--) {
            totalSeekTime += abs(currentPosition - movements[j]);
            currentPosition = movements[j];
        }
    } else {  
        for (i = numMovements - 1; i >= 0; i--) {
            if (movements[i] < currentPosition) {
                break;
            }
        }

        for (int j = i; j >= 0; j--) {
            totalSeekTime += abs(currentPosition - movements[j]);
            currentPosition = movements[j];
        }

        totalSeekTime += abs(currentPosition - 0);  
        currentPosition = 0;

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
    int direction = 1;  

    scan(movements, numMovements, currentPosition, direction);

    return 0;
}
