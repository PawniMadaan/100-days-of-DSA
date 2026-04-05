#include <stdio.h>
#include <stdlib.h>

// Queue structure
struct Queue {
    int *arr;
    int front, rear, size;
};

// Create Queue
struct Queue* createQueue(int n) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->arr = (int*)malloc(n * sizeof(int));
    q->front = 0;
    q->rear = -1;
    q->size = n;
    return q;
}

// Check if empty
int isEmpty(struct Queue* q) {
    return q->front > q->rear;
}

// Enqueue
void enqueue(struct Queue* q, int x) {
    if (q->rear < q->size - 1) {
        q->arr[++q->rear] = x;
    }
}

// Dequeue
int dequeue(struct Queue* q) {
    if (!isEmpty(q)) {
        return q->arr[q->front++];
    }
    return -1;
}

// BFS Function
void bfs(int n, int** adj, int* adjSize, int s) {
    int* visited = (int*)calloc(n, sizeof(int));
    struct Queue* q = createQueue(n);

    enqueue(q, s);
    visited[s] = 1;

    while (!isEmpty(q)) {
        int node = dequeue(q);
        printf("%d ", node);

        for (int i = 0; i < adjSize[node]; i++) {
            int neighbor = adj[node][i];
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                enqueue(q, neighbor);
            }
        }
    }
}

// Main function
int main() {
    int n = 5; // Number of vertices
    int** adj = (int**)malloc(n * sizeof(int*));
    int* adjSize = (int*)calloc(n, sizeof(int));

    // Initialize adjacency lists
    for (int i = 0; i < n; i++) {
        adj[i] = (int*)malloc(n * sizeof(int));
    }

    // Add edges (example graph)
    adj[0][0] = 1; adj[0][1] = 2;
    adjSize[0] = 2;

    adj[1][0] = 0; adj[1][1] = 3;
    adjSize[1] = 2;

    adj[2][0] = 0; adj[2][1] = 4;
    adjSize[2] = 2;

    adj[3][0] = 1;
    adjSize[3] = 1;

    adj[4][0] = 2;
    adjSize[4] = 1;

    printf("BFS starting from vertex 0: ");
    bfs(n, adj, adjSize, 0);
    printf("\n");

    // Free memory
    for (int i = 0; i < n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(adjSize);

    return 0;
}