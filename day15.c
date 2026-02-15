#include <stdio.h>

int main() {
    int m, n;
    
    scanf("%d %d", &m, &n);
    
    int matrix[m][n];
    int sum = 0;

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    if(m != n) {
        printf("Primary diagonal not possible");
        return 0;
    }

    for(int i = 0; i < m; i++) {
        sum += matrix[i][i];
    }

    printf("%d", sum);

    return 0;
}
