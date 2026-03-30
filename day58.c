#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int search(int inorder[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (inorder[i] == value)
            return i;
    }
    return -1;
}

struct Node* buildTree(int preorder[], int inorder[], int start, int end, int* preIndex) {
    if (start > end)
        return NULL;

    int curr = preorder[*preIndex];
    (*preIndex)++;

    struct Node* node = newNode(curr);

    if (start == end)
        return node;

    int inIndex = search(inorder, start, end, curr);

    node->left = buildTree(preorder, inorder, start, inIndex - 1, preIndex);
    node->right = buildTree(preorder, inorder, inIndex + 1, end, preIndex);

    return node;
}

void postorder(struct Node* root) {
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int main() {
    int n;
    scanf("%d", &n);

    int preorder[n], inorder[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &preorder[i]);

    for (int i = 0; i < n; i++)
        scanf("%d", &inorder[i]);

    int preIndex = 0;

    struct Node* root = buildTree(preorder, inorder, 0, n - 1, &preIndex);

    postorder(root);

    return 0;
}