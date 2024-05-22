#include <stdio.h>
#include <stdlib.h>

const int inf = 999999;
int k, a, b, u, v, n, ne = 1;
int mincost = 0;
int cost[10][10];  // Adjust size as needed
int p[10] = {0};  // Adjust size as needed

int applyfind(int i) {
    while(p[i] != 0)
        i = p[i];
    return i;
}

int applyunion(int i, int j) {
    if (i != j) {
        p[j] = i;
        return 1;
    }
    return 0;
}

int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix (enter %d for no edge):\n", inf);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0 && i != j) {
                cost[i][j] = inf;
            }
        }
    }

    printf("Minimum Cost Spanning Tree:\n");
    while (ne < n) {
        int min_val = inf;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (cost[i][j] < min_val) {
                    min_val = cost[i][j];
                    a = u = i;
                    b = v = j;
                }
            }
        }
        u = applyfind(u);
        v = applyfind(v);
        if (applyunion(u, v) != 0) {
            printf("%d -> %d\n", a, b);
            mincost += min_val;
        }
        cost[a][b] = cost[b][a] = inf;
        ne++;
    }
    printf("Minimum cost = %d\n", mincost);
    return 0;
}
