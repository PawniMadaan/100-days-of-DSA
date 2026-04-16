#include <stdio.h>
#include <stdlib.h>

struct Map {
    int sum;
    int index;
};

int maxLen(int arr[], int n) {
    int sum = 0, max_len = 0;

    // Create a map (size n)
    struct Map *map = (struct Map *)malloc(n * sizeof(struct Map));
    int mapSize = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];

        // Case 1: sum becomes 0
        if (sum == 0) {
            max_len = i + 1;
        }

        int found = 0;
        for (int j = 0; j < mapSize; j++) {
            if (map[j].sum == sum) {
                int len = i - map[j].index;
                if (len > max_len)
                    max_len = len;
                found = 1;
                break;
            }
        }

        if (!found) {
            map[mapSize].sum = sum;
            map[mapSize].index = i;
            mapSize++;
        }
    }

    free(map);
    return max_len;
}

int main() {
    int arr[] = {15, -2, 2, -8, 1, 7, 10, 23};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", maxLen(arr, n));

    return 0;
}