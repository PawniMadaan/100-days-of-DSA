#include <stdio.h>
#include <string.h>

#define MAX 100

int pq[MAX];
int size = 0;

void insert(int x)
{
    if(size == MAX)
    {
        printf("Queue Overflow\n");
        return;
    }

    pq[size++] = x;
}

int findMin()
{
    if(size == 0)
        return -1;

    int minIndex = 0;

    for(int i = 1; i < size; i++)
    {
        if(pq[i] < pq[minIndex])
            minIndex = i;
    }

    return minIndex;
}

int deletePQ()
{
    if(size == 0)
        return -1;

    int minIndex = findMin();
    int value = pq[minIndex];

    for(int i = minIndex; i < size - 1; i++)
        pq[i] = pq[i + 1];

    size--;

    return value;
}

int peek()
{
    if(size == 0)
        return -1;

    int minIndex = findMin();
    return pq[minIndex];
}

int main()
{
    int n, x;
    char op[10];

    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        scanf("%s", op);

        if(strcmp(op, "insert") == 0)
        {
            scanf("%d", &x);
            insert(x);
        }
        else if(strcmp(op, "delete") == 0)
        {
            printf("%d\n", deletePQ());
        }
        else if(strcmp(op, "peek") == 0)
        {
            printf("%d\n", peek());
        }
    }

    return 0;
}