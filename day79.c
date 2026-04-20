#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 1000

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

// Distance array
int dist[MAX];

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

    newNode = createNode(u, w);
    newNode->next = adj[v];
    adj[v] = newNode;
}

void swap(struct HeapNode* a, struct HeapNode* b) {
    struct HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct HeapNode heap[], int size, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < size && heap[left].dist < heap[smallest].dist)
        smallest = left;

    if (right < size && heap[right].dist < heap[smallest].dist)
        smallest = right;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        heapify(heap, size, smallest);
    }
}

// Extract min
struct HeapNode extractMin(struct HeapNode heap[], int *size) {
    struct HeapNode root = heap[0];
    heap[0] = heap[*size - 1];
    (*size)--;
    heapify(heap, *size, 0);
    return root;
}

void dijkstra(int n, int source) {
    struct HeapNode heap[MAX];
    int heapSize = 0;

    // Initialize distances
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }

    dist[source] = 0;

    heap[heapSize++] = (struct HeapNode){source, 0};

    while (heapSize > 0) {
        struct HeapNode minNode = extractMin(heap, &heapSize);
        int u = minNode.vertex;

        struct Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int weight = temp->weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;

                heap[heapSize++] = (struct HeapNode){v, dist[v]};
                // Fix heap
                for (int i = heapSize/2 - 1; i >= 0; i--)
                    heapify(heap, heapSize, i);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        adj[i] = NULL;
    }

    int u, v, w;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
    }

    int source;
    scanf("%d", &source);

    dijkstra(n, source);

    for (int i = 1; i <= n; i++) {
        printf("%d ", dist[i]);
    }

    return 0;
}