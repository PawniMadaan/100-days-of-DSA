#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct QNode {
    struct Node* treeNode;
    int hd;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1)
        return NULL;

    struct Node* root = newNode(arr[0]);

    struct Node* queue[n];
    int front = 0, rear = 0;

    queue[rear++] = root;
    int i = 1;

    while (i < n) {
        struct Node* curr = queue[front++];

        if (arr[i] != -1) {
            curr->left = newNode(arr[i]);
            queue[rear++] = curr->left;
        }
        i++;

        if (i < n && arr[i] != -1) {
            curr->right = newNode(arr[i]);
            queue[rear++] = curr->right;
        }
        i++;
    }

    return root;
}

void verticalOrder(struct Node* root) {
    if (!root) return;

    struct QNode queue[1000];
    int front = 0, rear = 0;

    int map[2000][100];
    int count[2000] = {0};

    int offset = 1000; 
    int minHD = 0, maxHD = 0;

    queue[rear++] = (struct QNode){root, 0};

    while (front < rear) {
        struct QNode temp = queue[front++];
        struct Node* node = temp.treeNode;
        int hd = temp.hd;

        map[hd + offset][count[hd + offset]++] = node->data;

        if (hd < minHD) minHD = hd;
        if (hd > maxHD) maxHD = hd;

        if (node->left)
            queue[rear++] = (struct QNode){node->left, hd - 1};

        if (node->right)
            queue[rear++] = (struct QNode){node->right, hd + 1};
    }

    for (int i = minHD; i <= maxHD; i++) {
        for (int j = 0; j < count[i + offset]; j++) {
            printf("%d ", map[i + offset][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct Node* root = buildTree(arr, n);

    verticalOrder(root);

    return 0;
}