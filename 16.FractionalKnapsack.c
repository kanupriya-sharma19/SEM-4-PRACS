#include <stdio.h>

struct Item {
    int value;
    int weight;
};

void bubbleSort(struct Item items[], int n) {
    for (int i=0; i<n-1; i++) {
        for (int j=i+1; j<n; j++) {
            double ratio1 = (double)items[i].value / items[i].weight;
            double ratio2 = (double)items[j].value / items[j].weight;
            if (ratio1 < ratio2) {
                struct Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }
}

double fractionalKnapsack(int capacity, struct Item items[], int n) {
    bubbleSort(items, n);
    double totalValue = 0.0;
    int currentWeight = 0;

    for (int i = 0; i < n; i++) {
        if (currentWeight + items[i].weight <= capacity) {
            totalValue += items[i].value;
            currentWeight += items[i].weight;
            printf("Took full item with value %d and weight %d\n", items[i].value, items[i].weight);
        } else {
            int remainingWeight = capacity - currentWeight;
            double fractionValue = (double)items[i].value / items[i].weight * remainingWeight;
            totalValue += fractionValue;
            printf("Took %.2f fraction of item with value %d and weight %d (i.e., %.2f value of %d weight)\n",
                (double)remainingWeight / items[i].weight,
                items[i].value,
                items[i].weight,
                fractionValue,
                remainingWeight
            );
            break;
        }
    }
    return totalValue;
}

int main() {
    int capacity = 50;
    struct Item items[] = {{60, 10}, {100, 20}, {120, 30}};
    int n = sizeof(items) / sizeof(items[0]);

    double maxValue = fractionalKnapsack(capacity, items, n);
    printf("Maximum value in knapsack = %.2f\n", maxValue);

    return 0;
}
