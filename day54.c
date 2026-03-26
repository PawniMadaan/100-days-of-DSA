#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Queue {
    int front, rear, size;
    struct Node* arr[100];
};

void initQueue(struct Queue* q) {
    q->front = q->rear = 0;
    q->size = 0;
}

int isEmpty(struct Queue* q) {
    return q->size == 0;
}

void enqueue(struct Queue* q, struct Node* node) {
    q->arr[q->rear++] = node;
    q->size++;
}

struct Node* dequeue(struct Queue* q) {
    q->size--;
    return q->arr[q->front++];
}

struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    struct Node* root = createNode(arr[0]);
    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    int i = 1;
    while (!isEmpty(&q) && i < n) {
        struct Node* current = dequeue(&q);

        if (i < n && arr[i] != -1) {
            current->left = createNode(arr[i]);
            enqueue(&q, current->left);
        }
        i++;

        if (i < n && arr[i] != -1) {
            current->right = createNode(arr[i]);
            enqueue(&q, current->right);
        }
        i++;
    }

    return root;
}

void zigzagTraversal(struct Node* root) {
    if (!root) return;

    struct Queue q;
    initQueue(&q);
    enqueue(&q, root);

    int leftToRight = 1;

    while (!isEmpty(&q)) {
        int levelSize = q.size;
        int arr[100];
        int index = 0;

        for (int i = 0; i < levelSize; i++) {
            struct Node* temp = dequeue(&q);
            arr[index++] = temp->data;

            if (temp->left)
                enqueue(&q, temp->left);
            if (temp->right)
                enqueue(&q, temp->right);
        }

        if (leftToRight) {
            for (int i = 0; i < index; i++)
                printf("%d ", arr[i]);
        } else {
            for (int i = index - 1; i >= 0; i--)
                printf("%d ", arr[i]);
        }

        leftToRight = !leftToRight;
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[100];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct Node* root = buildTree(arr, n);

    zigzagTraversal(root);

    return 0;
}