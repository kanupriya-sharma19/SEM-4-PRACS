#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NODES 5
#define INF INT_MAX

int adj[NODES][NODES] = {
    { 0, 2, 0, 6, 0 },
    { 2, 0, 3, 8, 5 },
    { 0, 3, 0, 0, 7 },
    { 6, 8, 0, 0, 9 },
    { 0, 5, 7, 9, 0 }
};

int parent[NODES];

int srcArr[NODES * NODES];
int destArr[NODES * NODES];
int weightArr[NODES * NODES];

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionOp(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

void swap(int *a, int *b) {
    int temp=*a;
    *a=*b;
    *b=temp;
}

void sortEdges(int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i+1; j < count; j++) {
            if (weightArr[i] > weightArr[j]) {
                swap(&weightArr[i], &weightArr[j]);
                swap(&srcArr[i], &srcArr[j]);
                swap(&destArr[i], &destArr[j]);
            }
        }
    }
}

void Kruskal(int totalEdges) {
    int edgeCount = 0;
    int totalCost = 0;

    sortEdges(totalEdges);

    for (int i = 0; i < NODES; i++)
        parent[i] = i;

    printf("Minimum Spanning Tree:\n");

    for (int i = 0; i < totalEdges; i++) {
        int src = srcArr[i];
        int dest = destArr[i];
        int srcParent = find(src);
        int destParent = find(dest);

        if (srcParent != destParent) {
            printf("%d - %d: %d\n", src, dest, weightArr[i]);
            totalCost += weightArr[i];
            unionOp(srcParent, destParent);
            edgeCount++;
        }

        if (edgeCount == NODES - 1)
            break;
    }

    printf("Total Cost: %d\n", totalCost);
}

int main() {
    int edgeIndex = 0;

    for (int i = 0; i < NODES; i++) {
        for (int j = i + 1; j < NODES; j++) {
            if (adj[i][j] != 0) {
                srcArr[edgeIndex] = i;
                destArr[edgeIndex] = j;
                weightArr[edgeIndex] = adj[i][j];
                edgeIndex++;
            }
        }
    }

    Kruskal(edgeIndex);
    return 0;
}
