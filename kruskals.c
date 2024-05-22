#include <stdio.h>
#include <stdlib.h>

#define MAX 100
#define INF 999999

// A structure to represent a weighted edge in a graph
struct Edge {
    int src, dest, weight;
};

// A structure to represent a subset for union-find
struct subset {
    int parent;
    int rank;
};

// Function prototypes
int find(struct subset subsets[], int i);
void Union(struct subset subsets[], int x, int y);
int compare(const void* a, const void* b);
void KruskalMST(int graph[MAX][MAX], int V);

int main() {
    int V;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    int graph[MAX][MAX];

    printf("Enter the adjacency matrix (use %d to represent infinity):\n", INF);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    KruskalMST(graph, V);

    return 0;
}

// A function to find the subset of an element i
int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// A function that does union of two sets of x and y
void Union(struct subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Compare two edges according to their weights
int compare(const void* a, const void* b) {
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

// The main function to construct MST using Kruskal's algorithm
void KruskalMST(int graph[MAX][MAX], int V) {
    struct Edge edges[MAX * MAX];
    int edgeCount = 0;

    // Convert adjacency matrix to edge list
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph[i][j] != INF) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = j;
                edges[edgeCount].weight = graph[i][j];
                edgeCount++;
            }
        }
    }

    // Step 1: Sort all the edges in non-decreasing order of their weight
    qsort(edges, edgeCount, sizeof(edges[0]), compare);

    // Allocate memory for creating V subsets
    struct subset* subsets = (struct subset*)malloc(V * sizeof(struct subset));

    // Create V subsets with single elements
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    struct Edge result[MAX];  // This will store the resultant MST
    int e = 0;  // An index variable, used for result[]
    int i = 0;  // An index variable, used for sorted edges

    // Number of edges to be taken is equal to V-1
    while (e < V - 1 && i < edgeCount) {
        // Step 2: Pick the smallest edge. Check if it forms a cycle with the MST formed so far
        struct Edge next_edge = edges[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // If including this edge does not cause a cycle, include it in result
        // and increment the index of result for the next edge
        if (x != y) {
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
        // Else discard the next_edge
    }

    // Print the contents of result[] to display the built MST
    printf("Following are the edges in the constructed MST\n");
    for (i = 0; i < e; ++i) {
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);
    }

    // Free allocated memory
    free(subsets);
}
