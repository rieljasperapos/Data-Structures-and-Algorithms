#include <stdio.h>

#define GSIZE 8
#define INF 99999

typedef int Graph[GSIZE][GSIZE];

void floyd(Graph A, Graph G);
void printGraph(Graph G);

int main() {
  // Graph myGraph = {
  //   {INF, 3, INF, 5},
  //   {2, INF, INF, 8},
  //   {INF, 1, INF, INF},
  //   {INF, INF, 2, INF}
  // };

    Graph myGraph = {
        {INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, 5, 9, INF, INF, 1, INF},
        {INF, 5, INF, INF, 2, INF, INF, INF},
        {INF, 9, INF, INF, INF, 6, INF, INF},
        {INF, INF, 2, INF, INF, INF, 8, INF},
        {INF, INF, INF, 6, INF, INF, 1, INF},
        {INF, 1, INF, INF, 8, 1, INF, 5},
        {INF, INF, INF, INF, INF, INF, 5, INF}
    };

  printf("Directed Graph: \n");
  printGraph(myGraph);
  Graph floydsAlgo = {0};
  printf("\nInitially Empty Graph: \n");
  printGraph(floydsAlgo);
  floyd(floydsAlgo, myGraph);
  printf("\nMinimum cost of all pair of nodes\n");
  printGraph(floydsAlgo);

  return 0;
}

void floyd(Graph A, Graph G) {
  int i, j, k;

  for (i = 0; i < GSIZE; i++) {
    for (j = 0; j < GSIZE; j++) {
      A[i][j] = G[i][j];
    }
  }

  for (i = 0; i < GSIZE; i++) {
    A[i][i] = 0;
  }

  for (k = 0; k < GSIZE; k++) {
    for (i = 0; i < GSIZE; i++) {
      for (j = 0; j < GSIZE; j++) {
        if (A[i][k] + A[k][j] < A[i][j]) {
          A[i][j] = A[i][k] + A[k][j];
        }
      }
    }
  }
}

void printGraph(Graph G) {
  int i, j;
  for (i = 0; i < GSIZE; i++) {
    for (j = 0; j < GSIZE; j++) {
      (G[i][j] == INF) ? printf("%-6s ", "INF") : printf("%-6d ", G[i][j]);
    }
    printf("\n");
  }
}