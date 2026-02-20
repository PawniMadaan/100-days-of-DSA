#include <stdio.h>
#include <stdlib.h>

#define MAX 100000
#define OFFSET 100000 

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    long long prefixSum = 0;
    long long count = 0;

    int *freq = (int *)calloc(2 * MAX + 1, sizeof(int));

    freq[OFFSET] = 1;

    for(int i = 0; i < n; i++) {
        prefixSum += arr[i];

        if(freq[prefixSum + OFFSET] > 0) {
            count += freq[prefixSum + OFFSET];
        }

        freq[prefixSum + OFFSET]++;
    }

    printf("%lld\n", count);

    free(freq);
    return 0;
}