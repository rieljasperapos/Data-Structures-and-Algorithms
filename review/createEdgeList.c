#include <stdio.h>
#include <stdlib.h>

#define SENTINEL 999
#define MAX_VERTEX 4
#define ARRAY_SIZE 20

typedef struct {
  int u, v;
  int weight;
} edgeType;

typedef struct node {
  edgeType edges[ARRAY_SIZE];
  int lastEdge;
} *edgeList;

typedef int adjMatrix[MAX_VERTEX][MAX_VERTEX];

edgeList createEdgeList(adjMatrix M);
void displayEdgeList(edgeList L);

int main() {
  adjMatrix M = {
    { SENTINEL, 16, 1, 8 }, 
    { 16, SENTINEL, 15, 24 }, 
    { 1, 15, SENTINEL, 30 }, 
    { 8, 24, 30, SENTINEL }
  };

  edgeList myEdgeList = NULL;
  myEdgeList = createEdgeList(M);

  displayEdgeList(myEdgeList);
  printf("last index: %d\n", myEdgeList->lastEdge);

  return 0;
}

// edgeList createEdgeList(adjMatrix M) {
//   edgeList retList = malloc(sizeof(struct node));
//   retList->lastEdge = -1;
//   int row, col, indx;

//   for (row = 0; row < MAX_VERTEX; row++) {
//     for (col = 0; col < MAX_VERTEX; col++) {
//       if (M[row][col] != SENTINEL && row > col) {
//         if (retList->lastEdge < ARRAY_SIZE - 1) {
//           for (indx = retList->lastEdge; indx >= 0 && retList->edges[indx].weight > M[row][col]; indx--) {
//             retList->edges[indx + 1] = retList->edges[indx];
//           }
//           edgeType temp;
//           temp.v = row;
//           temp.u = col;
//           temp.weight = M[row][col];

//           retList->edges[indx + 1] = temp;
//           retList->lastEdge++;
//         }
//       }
//     }
//   }
//   return retList;
// }

edgeList createEdgeList(adjMatrix M) {
  edgeList retVal = (edgeList)malloc(sizeof(struct node));
  if (retVal != NULL) {
    retVal->lastEdge = -1; // Initialize edge list
    int row, col;
    // Traversing adjacency matrix
    for (row = 0; row < MAX_VERTEX; row++) {
      for (col = row+1; col < MAX_VERTEX; col++) {
        // Check if there is an edge, and if the array is not yet full
        if (M[row][col] != SENTINEL && retVal->lastEdge != ARRAY_SIZE - 1) {
          int indx;
          // Insert sorted (ascending order)
          for (indx = retVal->lastEdge; indx >= 0 && retVal->edges[indx].weight > M[row][col]; indx--) {
            retVal->edges[indx + 1] = retVal->edges[indx];
          }
          retVal->edges[indx + 1].weight = M[row][col];
          retVal->edges[indx + 1].u = row;
          retVal->edges[indx + 1].v = col;
          retVal->lastEdge++;
        }
      }
    }
  }
  return retVal;
}

void displayEdgeList(edgeList L) {
  int indx;
  for (indx = 0; indx <= L->lastEdge; indx++) {
    printf("(%d, %d): %d\n", L->edges[indx].u, L->edges[indx].v, L->edges[indx].weight);
  }
}