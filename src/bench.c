#include <stdio.h>
#include <limits.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
// #define V 30000

int num;

int minKeySeq(int key[], int visited[], int V)
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

void primMSTSeq(int **graph, int V)
{
    double startSeq = omp_get_wtime();
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
        int u = minKeySeq(key, visited, V);

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
    double endSeq = omp_get_wtime();
    printf("%f, ", endSeq - startSeq);
    // printMST(from, V, graph);
}

int minKey(int key[], int visited[], int V)
{
    int min = INT_MAX, index, i;
omp_set_num_threads(4);
#pragma omp parallel
    {
        num = omp_get_num_threads();
        int index_local = index;
        int min_local = min;
#pragma omp for nowait
        for (i = 0; i < V; i++)
        {
            if (visited[i] == 0 && key[i] < min_local)
            {
                min_local = key[i];
                index_local = i;
            }
        }
#pragma omp critical
        {
            if (min_local < min)
            {
                min = min_local;
                index = index_local;
            }
        }
    }
    return index;
}

void printMST(int from[], int n, int **graph, int V)
{
    int i;
    printf("Edge   Weight\n");
    for (i = 1; i < V; i++)
        printf("%d - %d    %d \n", from[i], i, graph[i][from[i]]);
}

void primMST(int **graph, int V)
{
    double start = omp_get_wtime();
    
    int from[V];
    int key[V], num_threads;
    int visited[V];
    int i, count;
    for (i = 0; i < V; i++)
        key[i] = INT_MAX, visited[i] = 0;

    key[0] = 0;
    from[0] = -1;

    for (count = 0; count < V - 1; count++)
    {
        int u = minKey(key, visited, V);
        visited[u] = 1;

        int v;
#pragma omp parallel for schedule(static)
        for (v = 0; v < V; v++)
        {
            if (graph[u][v] && visited[v] == 0 && graph[u][v] < key[v])
                from[v] = u, key[v] = graph[u][v];
        }
    }
    double end = omp_get_wtime();
    printf("%f, %d\n", end - start, num);
    // printMST(from, V, graph);
    // printf("\n%d threads are created in primMST\n", num_threads);
}
int main(int argc, char *argv[])
{
    // int graph[V][V];
    int V = atoi(argv[1]);
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
    //Print adjacency matrix
    // for (i = 0; i < V; i++)
    // {
    //     for (j = 0; j < V; j++)
    //     {
    //         printf("%d ", graph[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d, ", V);
    primMSTSeq(graph, V);
    primMST(graph, V);

    return 0;
}
