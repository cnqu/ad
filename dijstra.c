
#include <limits.h>
#include <stdbool.h>
#include <limits.h>
#define V 6


int minDist(int dist[],     bool sptSet[]){
int min= INT_MAX, min_index;     //int min = INT_MAX;     int  min_index;`
for(int i=0;i<V;i++){
    if(sptSet[i]==false && dist[i]<=min){
        min=dist[i];
        min_index=i;
    }
}
return min_index;
}

void printSolution(int dist[], int parent[], int src, int dest) {
    printf("Vertex \t\t Distance from Source \t Path\n");
    printf("%d --> %d \t\t\t %d \t\t\t\t", src, dest, dist[dest]);
     printf("%d ", src);
    printPath(parent, dest);
   
    printf("\n");
}

void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
    printPath(parent, parent[j]);
    printf("%d ", j);
}



void dijkstra(int graph[V][V], int src, int dest){
        int dist[V];
        bool sptSet[V];
        
    int parent[V];
        for(int i=0;i<V;i++){
            dist[i]=INT_MAX;
            
             sptSet[i] = false;
                      parent[i] = -1;
        }
        dist[src]=0;
        for(int i=0;i<V-1;i++){
            int u=minDist(dist,sptSet);
            sptSet[u]=true;
            for(int v=0;v<V;v++){
                if (u == dest)
                break; 
                    if(!sptSet[v] && graph[u][v] && dist[u]!=INT_MAX && dist[u]+ graph[u][v]<dist[v]){
                                parent[v] = u;
                        dist[v]=dist[u]+ graph[u][v];
                    }
            }
        }
    printSolution(dist, parent, src, dest);
}

int main()
{
    // int graph[V][V] = { { 0, 1, 0, 0, 0, 8},
    //                     { 1, 0, 3, 0, 2, 0},
    //                     { 0, 3, 0, 4, 0, 0},
    //                     { 0, 0, 4, 0, 10, 0},
    //                     { 0, 2, 0, 10, 0, 7},
    //                     { 8, 0, 0, 0, 7, 0},
    //                     };


    int graph[V][V];
      printf("Enter the adjacency matrix for the graph:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
 int src, dest;
    printf("Enter source and destination vertices (0 to 8): ");
    scanf("%d %d", &src, &dest);

    if (src < 0 || src >= V || dest < 0 || dest >= V) {
        printf("Invalid source or destination vertex.\n");
        return 1;
    }

    dijkstra(graph, src, dest);
    // Function call

    return 0;
}
