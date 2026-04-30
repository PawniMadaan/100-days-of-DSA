#include <stdio.h>

int isPossible(int arr[], int n, int m, int maxPages) {
    int students = 1;
    int pages = 0;

    for (int i = 0; i < n; i++) {

        if (arr[i] > maxPages)
            return 0;

        if (pages + arr[i] > maxPages) {
            students++;
            pages = arr[i];

            if (students > m)
                return 0;
        } else {
            pages += arr[i];
        }
    }

    return 1;
}

int allocateBooks(int arr[], int n, int m) {

    int low = 0, high = 0;
    int ans = -1;

    for (int i = 0; i < n; i++) {
        high += arr[i];
        if (arr[i] > low)
            low = arr[i];
    }

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (isPossible(arr, n, m, mid)) {
            ans = mid;
            high = mid - 1; // Try smaller maximum
        } else {
            low = mid + 1;
        }
    }

    return ans;
}

int main() {
    int n, m;

    scanf("%d %d", &n, &m);

    int arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("%d\n", allocateBooks(arr, n, m));

    return 0;
}