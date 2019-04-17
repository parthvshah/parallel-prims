// A C / C++ program for Prim's Minimum Spanning Tree (MST) algorithm.
// The program is for adjacency matrix representation of the graph

#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>

// Number of vertices in the graph
#define V 10000

// A function to find the vertex with minimum key value, from the set of vertices not yet included in MST
int minKey(int key[], int visited[])
{
    // Initialize min value
    int min = INT_MAX, min_index;
    int v;
    for (v = 0; v < V; v++)
    {
        if (visited[v] == 0 && key[v] < min)
        {
            min = key[v], min_index = v;
        }
    }

    return min_index;
}

// A function to print the constructed MST stored in from[]
int printMST(int from[], int n, int **graph)
{
    int i;
    printf("Edge   Weight\n");
    for (i = 1; i < V; i++)
        printf("%d - %d    %d \n", from[i], i, graph[i][from[i]]);
}

void primMST(int **graph)
{
    int from[V];    // Array to store constructed MST
    int key[V];     // Key values used to pick minimum weight edge in cut
    int visited[V]; // To represent set of vertices not yet included in MST
    int i, count;
    // Initialize all keys as INFINITE
    for (i = 0; i < V; i++)
        key[i] = INT_MAX, visited[i] = 0;

    //start with first vertex
    key[0] = 0;   // Make key 0 so that this vertex is picked as first vertex
    from[0] = -1; // First node is always root of MST

    // The MST will have V vertices
    for (count = 0; count < V - 1; count++)
    {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, visited);

        // Add the picked vertex to the MST Set
        visited[u] = 1;
        int v;

        // Update key value and from index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (v = 0; v < V; v++)
            if (graph[u][v] && visited[v] == 0 && graph[u][v] < key[v])
                from[v] = u, key[v] = graph[u][v];
    }
    // printMST(from, V, graph);
}

// driver program to test above function
int main()
{
    // int graph[V][V];
    int **graph = (int **)malloc(V * sizeof(int *)); 
    for (int x=0; x<V; x++) 
        graph[x] = (int *)malloc(V * sizeof(int));
    int i, j;
    
    //Generate random adjacency matrix
    srand(time(NULL));
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            graph[i][j] = rand() % 10;

    for (i = 0; i < V; i++)
    {
        graph[i][i] = 0;
    }

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            graph[j][i] = graph[i][j];

    // for (i = 0; i < V; i++)
    // {
    //     for (j = 0; j < V; j++)
    //     {
    //         printf("%d ", graph[i][j]);
    //     }
    //     printf("\n");
    // }

    clock_t begin = clock();
    primMST(graph);
    clock_t end = clock();

    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time for seq = %f\n", time_spent);

    return 0;
}
