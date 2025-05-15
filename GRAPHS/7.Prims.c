#include <stdio.h>
#include <conio.h>
#include <limits.h>

#define NODES 5
#define INF INT_MAX

int mst[NODES];
int adj[NODES][NODES] = {

	{ 0, 2, 0, 6, 0 },
    { 2, 0, 3, 8, 5 },
                        		{ 0, 3, 0, 0, 7 },
                        		{ 6, 8, 0, 0, 9 },
                        		{ 0, 5, 7, 9, 0 }
};

struct Vertices {
	int dist;
	int parent;
	int visited;
} V[NODES];


int extractMin() {
	int min = INF;
	int minIndex = -1;
	for (int i = 0; i < NODES; i++) {
		if (!V[i].visited && V[i].dist < min) {
			min = V[i].dist;
			minIndex = i;
		}
	}
	return minIndex;
}


void Prims(int start) {
	for (int i = 0; i < NODES; i++) {
		V[i].dist = INF;
		V[i].parent = -1;
		V[i].visited = 0;
	}
	V[start].dist = 0;
	for (int i = 0; i < NODES; i++) {
		int u = extractMin();
		V[u].visited = 1;
		for (int v = 0; v < NODES; v++) {
			if (adj[u][v] && !V[v].visited && V[v].dist > adj[u][v]) {
				V[v].parent = u;
				V[v].dist = adj[u][v];
			}
		}
	}
	for (int i = 0; i < NODES; i++) {
		mst[i] = V[i].parent;
	}
}

int main() {
	int totalCost = 0;
		
	Prims(0);
	printf("Minimum Spanning Tree: \n");
	for (int i = 0; i < NODES; i++) {
		if (mst[i] != -1) {
			printf("%d - %d: %d\n", mst[i], i, adj[i][mst[i]]);
			totalCost += adj[i][mst[i]];
		}
	}
	printf("Total Cost: %d\n", totalCost);
	return 0;
}