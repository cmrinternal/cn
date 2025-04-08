#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 10

int graph[MAX][MAX];
int numnodes;
bool visited[MAX];

void primsMST(int start) {
    int parent[MAX];
    int key[MAX];
    for (int i = 0; i < numnodes; i++) {
        key[i] = INT_MAX;
        visited[i] = false;
    }
    key[start] = 0;
    parent[start] = -1;

    for (int count = 0; count < numnodes - 1; count++) {
        int min = INT_MAX, u;

        for (int v = 0; v < numnodes; v++) {
            if (!visited[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        visited[u] = true;

        for (int v = 0; v < numnodes; v++) {
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("\nMinimum Spanning Tree:\n");
    for (int i = 1; i < numnodes; i++) {
        printf("Edge: %c - %c, Weight: %d\n", 'A' + parent[i], 'A' + i, graph[i][parent[i]]);
    }
}

void broadcast(int current, int parent) {
    printf("Node %c received the packet.\n", 'A' + current);
    visited[current] = true;

    for (int i = 0; i < numnodes; i++) {
        if (graph[current][i] && !visited[i]) {
            broadcast(i, current);
        }
    }
}

int main() {
    printf("Enter number of nodes: ");
    scanf("%d", &numnodes);

    printf("Enter the adjacency matrix (enter 0 if no edge between nodes):\n");
    for (int i = 0; i < numnodes; i++) {
        for (int j = 0; j < numnodes; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int startNode;
    printf("Enter the starting node (0 to %d): ", numnodes - 1);
    scanf("%d", &startNode);

    primsMST(startNode);

   printf("\n starting broadcast");
   

    broadcast(startNode, -1);

    return 0;
}