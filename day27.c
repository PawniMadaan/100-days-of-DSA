#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    struct Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;
        
    temp->next = newNode;
}

int findIntersection(struct Node* head1, struct Node* head2) {
    struct Node* t1 = head1;
    
    while (t1 != NULL) {
        struct Node* p1 = t1;
        struct Node* p2 = head2;
        
        while (p2 != NULL) {
            struct Node* temp1 = p1;
            struct Node* temp2 = p2;
            
            while (temp1 != NULL && temp2 != NULL && temp1->data == temp2->data) {
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            
            if (temp2 == NULL)  
                return p1->data;
            
            p2 = p2->next;
        }
        t1 = t1->next;
    }
    
    return -1;
}

int main() {
    int n, m, x;
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &x);
        insertEnd(&head1, x);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &x);
        insertEnd(&head2, x);
    }

    int result = findIntersection(head1, head2);

    if (result == -1)
        printf("No Intersection");
    else
        printf("%d", result);

    return 0;
}