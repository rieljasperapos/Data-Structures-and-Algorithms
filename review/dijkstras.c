#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// #define GSIZE 4
#define GSIZE 8
#define INF 9999
typedef int SET[GSIZE];
// typedef unsigned char SET;
typedef int Graph[GSIZE][GSIZE];
typedef int Vertex;

int *dijkstrasAlgo(Graph G, Vertex V);
void displayDistanceList(int *arr);

int main() {
  // Graph Graph = {
  //   {INF, 10, 4, 15},
  //   {INF, INF, 6, 2},
  //   {INF, INF, INF, INF},
  //   {INF, INF, 7, INF}
  // };

  Graph Graph = {
        {INF, INF, INF, INF, INF, INF, INF, INF},
        {INF, INF, 5, 9, INF, INF, 1, INF},
        {INF, 5, INF, INF, 2, INF, INF, INF},
        {INF, 9, INF, INF, INF, 6, INF, INF},
        {INF, INF, 2, INF, INF, INF, 8, INF},
        {INF, INF, INF, 6, INF, INF, 1, INF},
        {INF, 1, INF, INF, 8, 1, INF, 5},
        {INF, INF, INF, INF, INF, INF, 5, INF}
    };
  
  int *distanceList = dijkstrasAlgo(Graph, 1);
  displayDistanceList(distanceList);

  return 0;
}

int min(int A, int B) {
    return (A < B) ? A : B;
}

// int *getElems(SET A) {
//     int size = sizeof(char) * 8;
//     int *retVal = NULL;
//     int count = 0;
    
//     for (int indx = size - 1; indx >= 0; indx--) {
//         if ((A >> indx) & 1) { // Check if the bit at position indx is set
//             int *temp = realloc(retVal, sizeof(int) * (count + 2)); // Allocate space for the new value and terminator
//             if (temp != NULL) {
//               retVal = temp;
//               retVal[count++] = indx;
//             }
//         }
//     }
    
//     // Add terminator
//     retVal[count] = -1;
    
//     return retVal;
// }

// int *getElems(SET A) {
//     int *retVal = (int *)malloc(sizeof(int) * 1);
//     if (retVal != NULL) {
//         int size = sizeof(char) * 8;
//         int indx, count = 0;
//         SET mask = 1 << (size - 1);
//         for (indx = size - 1; indx >= 0 && mask > 0; indx--, mask >>= 1) {
//             if ((A & mask) != 0) {
//                 retVal[count++] = indx;
//                 retVal = realloc(retVal, sizeof(int) * (count + 1));
//             }
//         }
//         retVal[count] = -1;
//     }
//     return retVal;
// }

SET *DIFFERENCE(SET A, SET B) {
    SET *C = (SET *)calloc(GSIZE, sizeof(int));
    if (C != NULL) {
      int indx;
      for (indx = 0; indx < GSIZE; indx++) {
        (*C)[indx] = (A[indx] == 1 && B[indx] == 0) ? 1 : 0;
      }
    }
    return C;
}

// SET DIFFERENCE(SET A, SET B) {
//     return (A & ~B);
// }

// void UNION(SET *A, SET *B) {
//     *B = *A | *B;
// }

// SET findMinimumVertex(int *A, SET S) {
//     int size = sizeof(char) * 8;
//     SET mask = 1 << (size - 1);
//     int indx;
//     SET min = -1; // Initialize min to -1
//     for (indx = size - 1; indx >= 0 && mask > 0; indx--, mask >>= 1) {
//         if ((S & mask) != 0) {
//             if (min == -1 || A[indx] < A[min]) { // Compare with min index, not value
//                 min = indx; // Update min to the index of the minimum element
//             }
//         }
//     }
//     return min;
// }

// SET findMinimumVertex(int *A, SET S) {
//     int size = sizeof(char) * 8;
//     SET mask = 1 << size - 1;
//     int indx;
//     SET min = 0;
//     for (indx = size - 1; indx >= 0 && mask > 0; indx--, mask >>= 1) {
//         if ((S & mask) != 0) {
//             if (A[indx] < A[min]) {
//                 min = indx;
//             }
//         }
//     }
//     return min;
// }

void UNION(SET *A, SET *B) {
  int indx;
  for (indx = 0; indx < GSIZE; indx++) {
    (*A)[indx] = ((*A)[indx] == 1 || (*B)[indx] == 1) ? 1 : 0;
  }
}

SET *findMinimum(int *A, SET S) {
  SET *C = (SET *)calloc(GSIZE, sizeof(int));
  if (C != NULL) {
    int indx, min = 0;
    for (indx = 0; indx < GSIZE; indx++) {
      if (S[indx] == 1 && A[indx] < A[min]) {
        min = indx;
      }
    }
    for (indx = 0; indx < GSIZE; indx++) {
      (*C)[indx] = (indx == min) ? 1 : 0;
    }
  }
  return C;
}

void displayBitVector(SET S) {
  int indx;
  for(indx = 0; indx < GSIZE; indx++) {
    printf("S[%d]: %d\n", indx, S[indx]);
  }
}

int minVertex(SET S) {
  int indx, retVal = -1;
  for(indx = 0; indx < GSIZE; indx++) {
    if (S[indx] == 1) {
      retVal = indx;
    }
  }
  return retVal;
}

// int *dijkstrasAlgo(Graph G, Vertex V) {
//     int *retVal = (int *)calloc(GSIZE, sizeof(int));
//     if (retVal != NULL) {
//         int indx, col, row;
//         SET vertices = {1, 1, 1, 1}; // Bit-vector implementation of vertices
//         SET visitedVertices; // Bit-vector implementation of visited vertices
//         // make the chosen vertex visited by giving it a 1
//         for (indx = 0; indx < GSIZE; indx++) {
//             visitedVertices[indx] = (indx == V) ? 1 : 0;
//         }

//         // Set distances
//         for (row = 0, col = row; col < GSIZE; col++) {
//             retVal[col] = (G[row][col] != INF) ? G[row][col] : INF;
//         }
        
//         for (indx = 0; indx < GSIZE; indx++) {
//             // find vertex w in vertices that is not yet in visited
//             // such that retVal[w] is a minimum
//             SET *difference = DIFFERENCE(vertices, visitedVertices);
//             SET *minBitVector = findMinimum(retVal, *difference);
//             int minVal = minVertex(*minBitVector);
    
//             // add the vertex w to the visited vertices
//             UNION(&visitedVertices, minBitVector);

//             // for each vertices v in that is not yet visited
//             // Do retVal[v] = min(retVal[v], retVal[minVertex] + retVal[minVertex][v])
//             SET *unvisitedVertex = DIFFERENCE(vertices, visitedVertices);
//             for (int indx = 1; indx < GSIZE; indx++) {
//                 if ((*unvisitedVertex)[indx] == 1) {
//                     retVal[indx] = min(retVal[indx], retVal[minVal] + G[minVal][indx]);
//                 }
//             }
            
//         }
//         retVal[V] = 0; // Set the chosen vertex weight to 0
//     }
//     return retVal;
// }

int *dijkstrasAlgo(Graph G, Vertex V) {
    int *retVal = (int *)calloc(GSIZE, sizeof(int));
    if (retVal != NULL) {
        int indx, col, row;
        SET visitedVertices = {0}; // Bit-vector implementation of visited vertices
        // make the chosen vertex visited by giving it a 1
        visitedVertices[V] = 1;

        // Set the default distances
        for (col = 0; col < GSIZE; col++) {
            retVal[col] = (G[V][col] != INF) ? G[V][col] : INF;
        }
        
        for (indx = 0; indx < GSIZE; indx++) {
            int idx, minVal = INF, minVertex;
            /*
              find vertex w in vertices that is not yet visited
              such that retVal[w] is a minimum
            */
            for (idx = 0; idx < GSIZE; idx++) {
              if (visitedVertices[idx] == 0 && retVal[idx] < minVal) {
                minVal = retVal[idx];
                minVertex = idx;
              }
            }

            visitedVertices[minVertex] = 1; // add the vertex w to the visited vertices

            /*
              for each vertices v that is not yet visited
              Do retVal[v] = min(retVal[v], retVal[minVertex] + retVal[minVertex][v])
            */
            for (idx = 0; idx < GSIZE; idx++) {
                if (visitedVertices[idx] == 0) {
                    retVal[idx] = min(retVal[idx], retVal[minVertex] + G[minVertex][idx]);
                }
            }
        }
        retVal[V] = 0; // Set the chosen vertex weight to 0
    }
    return retVal;
}

void displayDistanceList(int *arr) {
  int indx;
  for (indx = 0; indx < GSIZE; indx++) {
    printf("D[%d]: %d\n", indx, arr[indx]);
  }
}