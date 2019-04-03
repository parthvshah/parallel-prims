#include <stdio.h>
#include <limits.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#define V 1000

int minKey(int key[], int visited[])
{
    int min = INT_MAX, index, i;
#pragma omp parallel
    {
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

void printMST(int from[], int n, int graph[V][V])
{
    int i;
    printf("Edge   Weight\n");
    for (i = 1; i < V; i++)
        printf("%d - %d    %d \n", from[i], i, graph[i][from[i]]);
}

void primMST(int graph[V][V])
{
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
        int u = minKey(key, visited);
        visited[u] = 1;

        int v;

#pragma omp parallel for schedule(static)
        for (v = 0; v < V; v++)
        {
            if (graph[u][v] && visited[v] == 0 && graph[u][v] < key[v])
                from[v] = u, key[v] = graph[u][v];
        }
    }
    printMST(from, V, graph);
    printf("\n%d threads are created in primMST\n", num_threads);
}
int main()
{
    int graph[V][V];
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

    // double start = omp_get_wtime();
    clock_t start = clock();
    primMST(graph);
    // double end = omp_get_wtime();
    clock_t end = clock();
    // printf("Time = %.16g", end - start);
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%f\n", time_spent);

    return 0;
}
