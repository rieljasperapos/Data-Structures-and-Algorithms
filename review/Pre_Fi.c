// The Task 1

/******************************************************************
 * Project Name: BST and Priority Queue            			      *
 *                        										  *
 * Programmer  :  				                           		  *
 * Date Completed: April 29, 2023                                 *
 ******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VH_SIZE 0XF   // size of Virtual Heap
#define HEAP_SIZE 0XF // size of heap
/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef struct
{
  char name[24]; // Chocolate name
  int weight;    // Chocolate weight in grams
} chocoDesc;

typedef struct
{
  char prodID[8];     //  product ID uniquely identifies the products;
  chocoDesc prodDesc; //  product description
  float prodPrice;    //  product price
  int prodQty;        //  product count or quantity
} product;            //  product record

/**************************************
 * Cursor-based implementation of BST *
 **************************************/
typedef int BST; // Definition of BST

typedef struct
{
  product elem;
  int LC; // holds the index of the left child, -1 if there is no left child
  int RC; // holds the index of the Right Child; -1 if there is no right chidld
          // RC is USED as link to next available in the Virtual heap
} BSTnode;

/************************
 * Virtual Heap         *
 ************************/
typedef struct
{
  BSTnode VH_node[VH_SIZE];
  int avail;
} VHeap;

/**************************************
 * Definition of minHeap              *
 **************************************/
typedef struct
{
  product prod[HEAP_SIZE];
  int lastNdx; // Index of the last element in the array
} minHeap;

/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
//---Problem #1 ---
BST createMagicalBSTvheap(VHeap *VH);     // Complete
void displayVHeap(VHeap V);               // Partially coded
void displayProduct(product P);           // Complete
void displayBSTAscending(BST B, VHeap V); // To be coded

//---Problem #2 ---
void insert(BST *B, VHeap *VH, product P); // To be coded

//---Problem #3 ---
minHeap populate();
void displayHeap(minHeap HL);
void swapProduct(product *x, product *y);
void heapify(minHeap *H);
void heapifySubtree(minHeap *H, int subroot);

/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *   4)  Uncomment or copy the print statement in each PROBLEM#  if the task is     *
 *       completed.                                                                 *
 ***********************************************************************************/
int main()
{
  /*---------------------------------------------------------------------------------------
   * 	Problem #1 ::  1) Populate the Virtual heap and the BST by calling the function      *
   *                    createMagicalBSTvheap()                                            *
   *                 2) Call displayVHeap() to show the state of the virtual heap          *
   *                 3) Uncomment the printf() statement, then Call displayBSTAscending(). *                                  *
   *---------------------------------------------------------------------------------------*/
  printf("\n\n\nProblem #1:: ");
  printf("\n------------");
  // Declare variables needed for Problem #1
  VHeap myVH;
  BST tree;

  // Function Calls for Problem #1
  tree = createMagicalBSTvheap(&myVH);
  displayVHeap(myVH);

  printf("\n\nElements of BST B"); // Uncomment and put before the call displayBSTAscending()
  displayBSTAscending(tree, myVH);

  printf("\n\n");
  system("Pause");
  /*---------------------------------------------------------------------------------
   * 	Problem #2 ::  1) Call insert() passing the prod01, BST and virtual heap      *
   *                     in Problem 1.                                              *
   *                 2) Call insert() 3x, passing prod02, prod03, and prod04;       *
   *                    virtual heap in Problem 1, and an initially empty BST,      *
   *                    different from problem 1                                    *
   *                 3) Uncomment the printf() statement, then call                 *
   *                    displayBSTAscending() passing the new BST.                  *
   *                    Note: An alternative for the call to displayBSTAscending()  *
   *                          is a call to displayVHeap() and display the value of  *
   *                          the new BST.                                          *
   *--------------------------------------------------------------------------------*/
  printf("\n\n\nProblem #2:: ");
  printf("\n------------\n");
  // Declare variables needed for Problem #2
  BST newBst = -1;
  product prod01 = {"1109", {"Hersheys", 100}, 100.50, 10};
  product prod02 = {"1356", {"Ferrero", 200}, 250.75, 85};
  product prod03 = {"1807", {"Mars", 100}, 150.75, 20};
  product prod04 = {"1701", {"Toblerone", 50}, 90.75, 80};
  product prod05 = {"1569", {"Choco", 30}, 90.75, 80}; // Testing Purposes
  product prod06 = {"1699", {"Late", 30}, 90.75, 80};  // Testing Purposes
  product prod07 = {"1999", {"DSA:)", 30}, 90.75, 80}; // Testing Purposes

  // Function Calls for Problem #2
  insert(&tree, &myVH, prod01);
  insert(&newBst, &myVH, prod02);
  insert(&newBst, &myVH, prod03);
  insert(&newBst, &myVH, prod04);

  printf("\n\nElements of BST new");  //Uncomment and put before the call to displayBSTAscending()
  displayBSTAscending(newBst, myVH);

  printf("\n\n");
  system("pause");
  /*---------------------------------------------------------------------------------
   * 	Problem #3 ::  1) Calls function populate() and displayHeap()                  *
   *                 2) Calls function heapify() and displayHeap()                   *
   *--------------------------------------------------------------------------------*/
  printf("\n\n\nProblem #3:: ");
  printf("\n------------");
  // Declare variables needed for Problem #3
  minHeap myHeap;

  // Function Calls for Problem #3
  myHeap = populate();
  displayHeap(myHeap);
  heapify(&myHeap);
  displayHeap(myHeap);
}

/************************************************************
 *  Problem 1:: Function Definitions                          *
 ************************************************************/
BST createMagicalBSTvheap(VHeap *VH)
{
  VHeap v = {{
                 {{"1356", {"Ferrero", 200}, 250.75, 85}, 8, 2},
                 {{"1703", {"Toblerone", 100}, 125.75, 60}, -1, -1},
                 {{"1550", {"Cadbury", 120}, 200.00, 30}, 3, 13},
                 {{"1450", {"Ferrero", 100}, 150.50, 50}, 4, 10},
                 {{"1310", {"Nestle", 100}, 124.50, 70}, -1, -1},
                 {{"1688", {"Guylian", 50}, 99.75, 35}, -1, -1},
                 {{"1901", {"Reese", 135}, 150.75, 20}, -1, 11}, // 6
                 {{"1701", {"Toblerone", 50}, 90.75, 80}, 0, 9}, // root
                 {{"1109", {"Patchi", 50}, 99.75, 35}, -1, 14},
                 {{"1807", {"Mars", 100}, 150.75, 20}, 1, -1},
                 {{"1455", {"Tango", 75}, 49.50, 100}, -1, -1},  // 10
                 {{"1150", {"Valor", 120}, 149.50, 90}, -1, -1}, // 11
                 {{"1284", {"Lindt", 100}, 250.75, 15}, -1, -1}, // 12
                 {{"1601", {"Meiji", 75}, 75.50, 60}, -1, 5},    // 13
                 {{"1201", {"Kitkat", 50}, 97.75, 40}, -1, 12},  // 14
             },
             6};
  *VH = v;

  return 7;
}

void displayProduct(product P)
{
  printf("\n%-8s", P.prodID);
  printf("%-10s", P.prodDesc.name);
  printf("%-6d", P.prodDesc.weight);
  printf("%-10.2f", P.prodPrice);
  printf("%-6d", P.prodQty);
}

void displayBSTAscending(BST B, VHeap V)
{
  // Write your code here!!!
  if (B == -1)
  {
    return;
  }

  // Inorder traversal (recursive)
  displayBSTAscending(V.VH_node[B].LC, V);
  displayProduct(V.VH_node[B].elem);
  displayBSTAscending(V.VH_node[B].RC, V);
}

void displayVHeap(VHeap V)
{
  int x;

  printf("\n\nDetails of the Virtual Heap :: ");
  printf("\n------------------------------");
  printf("\nAvailable Index  :: %d", V.avail);

  printf("\n\n%10s", "Index");
  printf("%10s", "Prod ID");
  printf("%15s", "LC Field");
  printf("%15s", "RC Field");
  printf("\n%10s%10s%15s%15s", "-----", "-------", "--------", "--------");

  // Write your code here!!!
  int indx;
  for (indx = 0; indx < VH_SIZE; indx++)
  {
    printf("\n%10d", indx);
    printf("%10s", V.VH_node[indx].elem.prodID);
    printf("%15d", V.VH_node[indx].LC);
    printf("%15d", V.VH_node[indx].RC);
  }

  printf("\n\n");
  system("Pause");
}

/************************************************************
 *  Problem 2:: Function Definitions                         *
 ************************************************************/
void insert(BST *B, VHeap *VH, product P)
{
  // Write your code here!!!
  if (VH->avail != -1) {
    BST *trav;
    for (trav = B; *trav != -1 && strcmp(P.prodID, VH->VH_node[*trav].elem.prodID) != 0;) {
      if (strcmp(P.prodID, VH->VH_node[*trav].elem.prodID) < 0) { // If P is smaller go to left
        trav = &VH->VH_node[*trav].LC;
      } else { // else go right
        trav = &VH->VH_node[*trav].RC;
      }
    }
    if (*trav == -1) {
      int space = VH->avail;
      VH->avail = VH->VH_node[space].RC;
      VH->VH_node[space].elem = P;
      VH->VH_node[space].LC = -1;
      VH->VH_node[space].RC = -1;
      *trav = space;
      printf("Successful Insert of Product %s.\n", P.prodID);
    } else {
      printf("Unsuccessful Insert of Product %s: Element exists.\n", P.prodID);
    }
  } else {
    printf("Unsuccessful Insert of Product %s: Virtual Heap is Full.\n", P.prodID);
  }
}

/************************************************************
 *  Problem 3:: Function Definitions                        *
 ************************************************************/
minHeap populate()
{
  minHeap HL = {{{"1701", {"Toblerone", 50}, 90.75, 80},
                 {"1356", {"Ferrero", 200}, 250.75, 85},
                 {"1807", {"Mars", 100}, 150.75, 20},
                 {"1109", {"Patchi", 50}, 99.75, 35},
                 {"1550", {"Cadbury", 120}, 200.00, 30},
                 {"1201", {"Kitkat", 50}, 97.75, 40},
                 {"1450", {"Ferrero", 100}, 150.50, 50},
                 {"1601", {"Meiji", 75}, 75.50, 60},
                 {"1284", {"Lindt", 100}, 250.75, 15},
                 {"1310", {"Nestle", 100}, 124.50, 70},
                 {"1455", {"Tango", 75}, 49.50, 100},
                 {"1688", {"Guylian", 50}, 99.75, 35}},
                11};
  return HL;
}

void swapProduct(product *x, product *y)
{
  product temp;

  temp = *x;
  *x = *y;
  *y = temp;
}

void displayHeap(minHeap HL)
{
  int x;

  printf("\n\nList/Heap :: %d Elements", HL.lastNdx + 1); // Uncomment and COMPLETE this print statement
  printf("\n========================");

  // Write your code here!!!
  for (x = 0; x <= HL.lastNdx; x++) {
    printf("\n%-8s", HL.prod[x].prodID);
    printf("%-10s", HL.prod[x].prodDesc.name);
    printf("%-6d", HL.prod[x].prodDesc.weight);
    printf("%-10.2f", HL.prod[x].prodPrice);
    printf("%-6d", HL.prod[x].prodQty);
  }
}

void heapify(minHeap *H)
{
  // Write your code here!!!
  if (H->lastNdx != -1) { // to check if the heap is empty
    int parent;
    for (parent = (H->lastNdx - 1) / 2; parent >= 0; parent--) {
      heapifySubtree(H, parent);
    }
  }
}

void heapifySubtree(minHeap *H, int subroot)
{
  // Write your code here!!!
  int smallChild;
  // Get small child
  int LC = (subroot * 2) + 1;
  int RC = (subroot * 2) + 2;
  if (RC <= H->lastNdx) {
    smallChild = (strcmp(H->prod[LC].prodID, H->prod[RC].prodID) < 0) ? LC : RC;
  } else if (LC <= H->lastNdx) {
    smallChild = LC;
  }
  // smallChild = (strcmp(H->prod[LC].prodID, H->prod[RC].prodID) < 0) ? LC : RC;

  for (; smallChild != subroot && strcmp(H->prod[smallChild].prodID, H->prod[subroot].prodID) < 0;) {
    swapProduct(&(H->prod[subroot]), &(H->prod[smallChild]));

    // Push down until POT is satisfied
    subroot = smallChild;
    // Get small child again
    LC = (subroot * 2) + 1;
    RC = (subroot * 2) + 2;
    if (RC <= H->lastNdx) {
    smallChild = (strcmp(H->prod[LC].prodID, H->prod[RC].prodID) < 0) ? LC : RC;
  } else if (LC <= H->lastNdx) {
    smallChild = LC;
  }
    // smallChild = (strcmp(H->prod[LC].prodID, H->prod[RC].prodID) < 0) ? LC : RC;
  }
}
