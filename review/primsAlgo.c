#include <stdio.h>

#define INF 99999
#define GSIZE 6
typedef int Graph[GSIZE][GSIZE]; // Adjacent matrix
typedef int Vertex; // Arbitrary vertex
typedef int SET[GSIZE];

int primsAlgo(Graph G, Vertex V);

int main() {
  Graph myGraph = {
    {0, 1, 5, 4, 6, 5},
    {1, 0, 5, INF, INF, 6},
    {5, 5, 0, 2, INF, INF},
    {4, INF, 2, 0, 1, INF},
    {6, INF, INF, 1, 0, 3},
    {5, 6, INF, INF, 3, 0}
  };

  int totalCost = primsAlgo(myGraph, 2);
  printf("Total Cost: %d\n", totalCost);

  return 0;
}

// int primsAlgo(Graph G, Vertex V) {
//     SET visited = {0};
//     int cost[GSIZE];
//     int indx, jndx, count;
//     int retVal = 0;

//     // Set the cost of each vertex to INF and the starting vertex to 0
//     for (indx = 0; indx < GSIZE; indx++) {
//         cost[indx] = (V == indx) ? 0 : INF;
//     }

//     // Loop until all vertex are included in the spanning tree
//     for (count = 0; count < GSIZE; count++) {
//         // Find a vertex that is not yet visited and has a minimum cost value
//         int minCostIndx, minVal = INF;
//         for (indx = 0; indx < GSIZE; indx++) {
//             if (cost[indx] < minVal && visited[indx] == 0) {
//                 minVal = cost[indx];
//                 minCostIndx = indx;
//             }
//         }
//         // Set the vertex with minimum cost as visited
//         visited[minCostIndx] = 1;

//         // Adjust all adjacent vertices of the vertex with the minimum cost
//         for (jndx = 0; jndx < GSIZE; jndx++) {
//             /*
//               If weight of edge u,v is less than the cost value of v change the cost value to the weight of edge u,v
//               such that vertex v is not yet included in the spanning tree
//             */
//             if (visited[jndx] == 0 && G[minCostIndx][jndx] != INF && G[minCostIndx][jndx] < cost[jndx]) {
//                 cost[jndx] = G[minCostIndx][jndx];
//             }
//         }
//         // Add the minimum cost
//         retVal += cost[minCostIndx];
//     }
//   return retVal;
// }

int primsAlgo(Graph G, Vertex V) {
    SET visited = {0};
    int indx, jndx, count;
    int retVal = 0;
    // Include the starting vertex to the spanning tree
    visited[V] = 1;

    // Loop until all vertices is included in the spanning tree
    for (count = 0; count < GSIZE - 1; count++) {
        // find the minimum cost pair u, v such that u is in visitied and v is not visited
        int minVal = INF;
        int minIndx;
        for (indx = 0; indx < GSIZE; indx++) {
            for (jndx = 0; jndx < GSIZE && visited[indx] == 1; jndx++) {
                if (visited[jndx] == 0 && G[indx][jndx] < minVal) {
                    minVal = G[indx][jndx];
                    minIndx = jndx;
                }
            }
        }
        // Add the minimum vertex to the spanning tree
        visited[minIndx] = 1;
        retVal += minVal;  
    }
    return retVal;
}