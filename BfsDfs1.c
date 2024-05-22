#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

struct Graph {
    bool visitedNodes[MAX_NODES];
    int adjacencyList[MAX_NODES][MAX_NODES];
    int nodeCount;
};

void initGraph(struct Graph *graph) {
    graph->nodeCount = 0;
    for (int i = 0; i < MAX_NODES; i++) {
        graph->visitedNodes[i] = false;
        for (int j = 0; j < MAX_NODES; j++) {
            graph->adjacencyList[i][j] = 0;
        }
    }
}

void addNode(struct Graph *graph, int node) {
    if (node >= MAX_NODES) {
        printf("Exceeded maximum number of nodes.\n");
        return;
    }
    graph->nodeCount++;
}

void addEdge(struct Graph *graph, int node1, int node2) {
    if (node1 >= MAX_NODES || node2 >= MAX_NODES) {
        printf("Invalid node.\n");
        return;
    }
    graph->adjacencyList[node1][node2] = 1;
    graph->adjacencyList[node2][node1] = 1; // Assuming an undirected graph
}

void resetVisited(struct Graph *graph) {
    for (int i = 0; i < MAX_NODES; i++) {
        graph->visitedNodes[i] = false;
    }
}

void depthFirstSearch(struct Graph *graph, int startNode) {
    graph->visitedNodes[startNode] = true;
    printf("%d ", startNode);

    for (int i = 0; i < MAX_NODES; i++) {
        if (graph->adjacencyList[startNode][i] && !graph->visitedNodes[i]) {
            depthFirstSearch(graph, i);
        }
    }
}

void breadthFirstSearch(struct Graph *graph, int startNode) {
    bool visited[MAX_NODES] = { false };
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    visited[startNode] = true;
    queue[rear++] = startNode;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d ", currentVertex);

        for (int i = 0; i < MAX_NODES; i++) {
            if (graph->adjacencyList[currentVertex][i] && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
}

int main() {
    struct Graph graph;
    initGraph(&graph);            //// &graph hai

    int option;
    do {  
        printf("\nGraph Operations\n");
        printf("1. Add Node\n");
        printf("2. Add Edge\n");
        printf("3. Depth First Traversal\n");
        printf("4. Breadth First Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);   

        switch (option) {
            case 1: {
                int node;
                printf("Enter node to add: ");
                scanf("%d", &node);
                addNode(&graph, node);
                break;
            }
            case 2: {
                int node1, node2;
                printf("Enter nodes to add edge between (node1 node2): ");
                scanf("%d %d", &node1, &node2);
                addEdge(&graph, node1, node2);
                break;
            }
            case 3: {
                int startNode;
                printf("Enter starting node for Depth First Traversal: ");
                scanf("%d", &startNode);
                printf("Depth First Traversal: ");
                resetVisited(&graph);
                depthFirstSearch(&graph, startNode);
                printf("\n");
                break;
            }
            case 4: {
                int startNode;
                printf("Enter starting node for Breadth First Traversal: ");
                scanf("%d", &startNode);
                printf("Breadth First Traversal: ");
                breadthFirstSearch(&graph, startNode);
                printf("\n");
                break;
            }
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (option != 5);

    return 0;
}
