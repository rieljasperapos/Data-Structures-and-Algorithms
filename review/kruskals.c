#include <stdio.h>
#include <stdlib.h>

#define INF 99999
#define GSIZE 8

typedef int Graph[GSIZE][GSIZE];
typedef struct {
  int u, v;
  int weight;
} edgeType;

typedef struct {
  edgeType edges[GSIZE];
  int edgeCount;
  int minimumCost;
} MST;

MST kruskalMST(Graph G);
void displayMST(MST T);

int main() {
  // Graph myGraph = {
  //   {0, 1, 5, 4, 6, 5},
  //   {1, 0, 5, INF, INF, 6},
  //   {5, 5, 0, 2, INF, INF},
  //   {4, INF, 2, 0, 1, INF},
  //   {6, INF, INF, 1, 0, 3},
  //   {5, 6, INF, INF, 3, 0}
  // };

  Graph myGraph = {
    {0, 7, 0, 0, 0, 0, 0, 0},
    {7, 0, 0, 3, 0, 0, 3, 0},
    {0, 0, 0, 0, 2, 0, 0, 0},
    {0, 3, 0, 0, 0, 0, 0, 7},
    {0, 0, 2, 0, 0, 0, 0, 2},
    {0, 0, 0, 0, 0, 0, 5, 2},
    {0, 3, 0, 0, 0, 5, 0, 8},
    {0, 0, 0, 7, 2, 2, 8, 0},
  };

  MST minSpanningTree = kruskalMST(myGraph);
  displayMST(minSpanningTree);
}

/*
Steps to do kruskals
1. Initialize the MST that will be returned
2. Initialize also an array of components/parents
While(V is not in 1 component)
3. loop through the entire graph
  if (G[indx][jndx] < minVal && parent[indx] != parent[jndx]) (if there is an edge and they are not in the same group)
  a.) find the minimum cost edge u, v
  b.) hold u and v (int u = indx; int v = jndx), and the minimum value (minVal = G[indx][jndx])
4. Hold pu = parent[u], pv = parent[v]
5. if (pu != pv) 
    MST.edges[MST.edgeCount].u = u
    MST.edges[MST.edgeCount].v = v;
    MST.edges[MST.edgeCount].weight = minVal
    MST.minimumCost += minVal;
    for each parent[indx] (makes vertices into 1 group)
    if (parent[indx] == pv)
      parent[indx] = pu
*/
MST kruskalMST(Graph G) {
  MST retVal;
  int parent[GSIZE], indx, jndx, count;
  retVal.minimumCost = 0;
  retVal.edgeCount = 0;
  for (indx = 0; indx < GSIZE; indx++) {
    parent[indx] = indx;
  }
  for (retVal.edgeCount = 0; retVal.edgeCount < GSIZE - 1;) {
    int minVal = INF;
    int u,v;
    int pu, pv;
    for (indx = 0; indx < GSIZE; indx++) {
      for (jndx = 0; jndx < GSIZE; jndx++) {
        if (parent[indx] != parent[jndx] && G[indx][jndx] < minVal && G[indx][jndx] != 0) {
          minVal = G[indx][jndx];
          u = indx;
          v = jndx;
        }
      }
    }
    pu = parent[u];
    pv = parent[v];
    if (pu != pv) {
      retVal.edges[retVal.edgeCount].u = u;
      retVal.edges[retVal.edgeCount].v = v;
      retVal.edges[retVal.edgeCount].weight = minVal;
      retVal.minimumCost += minVal;
      retVal.edgeCount++;
      for (indx = 0; indx < GSIZE; indx++) {
        if (parent[indx] == pv) {
          parent[indx] = pu;
        }
      }
    }
  }
  return retVal;
}

void displayMST(MST T) {
  int indx;
  for (indx = 0; indx < T.edgeCount; indx++) {
    printf("(%d, %d): %d\n", T.edges[indx].u, T.edges[indx].v, T.edges[indx].weight);
  }
  printf("Total Cost: %d\n", T.minimumCost);
}

