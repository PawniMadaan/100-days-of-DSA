#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int V;
    struct Node* adj[MAX];
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    for (int i = 0; i < V; i++)
        graph->adj[i] = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = graph->adj[u];
    graph->adj[u] = newNode;
}

int dfsCycle(struct Graph* graph, int v, int visited[], int recStack[]) {
    visited[v] = 1;
    recStack[v] = 1;

    struct Node* temp = graph->adj[v];
    while (temp != NULL) {
        int adjVertex = temp->vertex;

        if (!visited[adjVertex]) {
            if (dfsCycle(graph, adjVertex, visited, recStack))
                return 1;
        }
        else if (recStack[adjVertex]) {
            return 1; // cycle found
        }

        temp = temp->next;
    }

    recStack[v] = 0; 
    return 0;
}

int isCyclic(struct Graph* graph) {
    int visited[MAX] = {0};
    int recStack[MAX] = {0};

    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            if (dfsCycle(graph, i, visited, recStack))
                return 1;
        }
    }
    return 0;
}

int main() {
    int V, E;
    scanf("%d %d", &V, &E);

    struct Graph* graph = createGraph(V);

    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    if (isCyclic(graph))
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}