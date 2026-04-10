#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

struct Node {
    int vertex;
    int weight;
    struct Node* next;
};

struct HeapNode {
    int vertex;
    int dist;
};

struct Node* adj[MAX];

int dist[MAX];

struct HeapNode heap[MAX];
int heapSize = 0;

void swap(struct HeapNode* a, struct HeapNode* b) {
    struct HeapNode temp = *a;
    *a = *b;
    *b = temp;
}
void heapifyUp(int i) {
    while (i && heap[i].dist < heap[(i - 1) / 2].dist) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void heapifyDown(int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && heap[left].dist < heap[smallest].dist)
        smallest = left;

    if (right < heapSize && heap[right].dist < heap[smallest].dist)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapifyDown(smallest);
    }
}

void push(int vertex, int distVal) {
    heap[heapSize].vertex = vertex;
    heap[heapSize].dist = distVal;
    heapifyUp(heapSize);
    heapSize++;
}

struct HeapNode pop() {
    struct HeapNode root = heap[0];
    heap[0] = heap[--heapSize];
    heapifyDown(0);
    return root;
}

struct Node* createNode(int v, int w) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = NULL;
    return newNode;
}

void addEdge(int u, int v, int w) {
    struct Node* newNode = createNode(v, w);
    newNode->next = adj[u];
    adj[u] = newNode;
}

void dijkstra(int V, int source) {
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;

    dist[source] = 0;
    push(source, 0);

    while (heapSize > 0) {
        struct HeapNode minNode = pop();
        int u = minNode.vertex;

        struct Node* temp = adj[u];

        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                push(v, dist[v]);
            }

            temp = temp->next;
        }
    }
}

int main() {
    int V = 5;

    for (int i = 0; i < V; i++)
        adj[i] = NULL;

    addEdge(0, 1, 10);
    addEdge(0, 4, 5);
    addEdge(1, 2, 1);
    addEdge(4, 1, 3);
    addEdge(4, 2, 9);
    addEdge(4, 3, 2);
    addEdge(2, 3, 4);
    addEdge(3, 0, 7);

    int source = 0;

    dijkstra(V, source);

    printf("Shortest distances from source %d:\n", source);
    for (int i = 0; i < V; i++) {
        printf("To %d = %d\n", i, dist[i]);
    }

    return 0;
}