#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

int adj[MAX][100];   
int size[MAX];       
int visited[MAX];

void dfs(int node) {
    visited[node] = 1;

    for (int i = 0; i < size[node]; i++) {
        int neighbor = adj[node][i];
        if (!visited[neighbor]) {
            dfs(neighbor);
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        size[i] = 0;
        visited[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        adj[u][size[u]++] = v;
        adj[v][size[v]++] = u;
    }

    // Run DFS from node 1
    dfs(1);

    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (visited[i]) count++;
    }

    if (count == n)
        printf("CONNECTED\n");
    else
        printf("NOT CONNECTED\n");

    return 0;
}