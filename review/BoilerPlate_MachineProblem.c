/******************************************************************
 * Project Name:  List, Set and Dictionary                        *
 * Programmer  :  Put your Name here                              *
 * Date Completed: March 25, 2023                                 *
 ******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VH_SIZE     0XC    //size of Virtual Heap
#define OPEN_DSIZE  0XA    //size of Open Hash Table
#define CLOSE_DSIZE 0XC    //size of Close Hash Table
#define LIST_SIZE   0XF    //size of the array implementation of List
/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef struct {  
	char name[24];          // Chocolate name  
 	int  weight;            // Chocolate weight in grams  
}chocoDesc;
 
typedef struct {
   char prodID[8];          //  product ID uniquely identifies the products; EMPTY or DELETED   
  	chocoDesc prodDesc;     //  product description 
 	float prodPrice;        //  product price 
  	int prodQty;            //  product count or quantity   
}product;                   //  product record  

typedef struct {
	product elem;            
	int next;                
}prodNode;                 // Product node, used in cursor-based implementation of Set  


/************************
 * Virtual Heap         *
 ************************/
typedef struct {
   prodNode VH_node[VH_SIZE];
   int avail;
}VHeap;

/******************************************
 * Cursor-Based Implementation of SET     *
 ******************************************/
typedef struct {
   int elemIndex;        // index of the 1st element in the set  
   int count;            // holds the actual number of elements in the set  
   VHeap *VHptr;         // holds the pointer to the virtual heap  
}cursorSet;            

/********************************************
 * Open Hashing Implementation of Dictionary*
 ********************************************/
typedef struct {
	int header[OPEN_DSIZE];  // array of sets   
	int count;               // total number of elements in the dictionary  
	VHeap *dicVHptr;         // holds the pointer to the virtual heap  
}openDic;


/**********************************************
 * Closed Hashing with 2 pass loading          *
 **********************************************/
#define EMPTY   "empty"     // stored in product ID field  
#define DELETED  "del"      // stored in product ID field * 
 
typedef product closeDic[CLOSE_DSIZE];   //Definition of the closed hash dictionary
  
typedef struct {
	product prod[LIST_SIZE];
	int last;   //index of the last element; -1 if list is empty	
}List;



/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
//---Problem #1 ---
void initVHeap(VHeap *VH);
cursorSet initCursorSet(VHeap *VH);
void displayVHeap(VHeap V);
void displaySet(cursorSet A);

//---Problem #2 ---
int mallocInVHeap(VHeap *VH);
void insertSorted(cursorSet *A, product P);
void populateSet(cursorSet *A);

//---Problem #3 ---
int openHash(char *IDen);                
openDic initOpenDict(VHeap *VH);
openDic convertToOpenDict(cursorSet *A);
void displayOpenDict(openDic D);

//---Problem #4 ---
void freeInVHeap(VHeap *VH, int ndx);
void deleteDict(openDic *D, char *IDen);

//---Problem #5 ---
int closeHash(char *ID);
void initCloseDict(closeDic CD);
closeDic * convertToCloseDict(openDic *D);	
void displayCloseDict(closeDic CD);


 
/************************************************************************************
 * READ ME FIRST before ANSWERING                                                   *
 *   1)  To facilitate the checking of the machine problem, follow the instructions *
 *       in each PROBLEM #.                                                         *
 *   2)  To accomplish the task for each PROBLEM, a series of function calls may be *
 *       necessary.                                                                 *  
 *   3)  Write you answer BELOW THE COMMENTS. DO NOT DELETE COMMENTS                *
 *                                                                                  *
 ***********************************************************************************/
 int main( ) 
 {	
 /*---------------------------------------------------------------------------------
 * 	Problem #1 ::  1) Initializes the virtual heap and the cursor Set             *
 *                 2) Displays the contents  virtual heap and cursor Set          *
 *--------------------------------------------------------------------------------*/
 	printf("\n\n\nProblem #1:: "); 
 	printf("\n------------");
 	//Declare variables needed for Problem #1
  VHeap VH;
  cursorSet mySet;
	
 	//Function Calls for Problem #1
  initVHeap(&VH);
  mySet = initCursorSet(&VH);
  displayVHeap(VH);
  displaySet(mySet);
	

/*---------------------------------------------------------------------------------
 * 	Problem #2 ::  1) Populates the Cursor set which is sorted in ascending order *
 *                    according to ID                                             *
 *                 2) Displays the Cursor set                                     * 
 *--------------------------------------------------------------------------------*/	 
 	printf("\n\n\nProblem #2:: "); 
 	printf("\n------------");
	//Declare variables needed for Problem #2

	
 	//Function Calls for Problem #2
  populateSet(&mySet);
  displaySet(mySet);

/*---------------------------------------------------------------------------------
 * 	Problem #3 ::  1) Converts the Cursor set into an Open Hash Dictionary        *      
 *                 2) Displays the Open Hash Dictionary                           *
 *                 3) Displays the empty Cursor set.                              * 
 *--------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #3:: "); 
 	printf("\n------------");
	//Declare variables needed for Problem #3
 	openDic myDic;
	
 	//Function Calls for Problem #3
  myDic = convertToOpenDict(&mySet);
  displayOpenDict(myDic);
  displaySet(mySet);


 

/*---------------------------------------------------------------------------------
 * 	Problem #4 ::  1) Perform 3 delete operations on the Open Hash Dictionary     *
 *                 2) Displays the Open Hash Dictionary                           *
 *                 3) Displays the Virtual Heap                                   * 
 *--------------------------------------------------------------------------------*/	
 	printf("\n\n\nProblem #4:: "); 
 	printf("\n------------");	
 //Declare variables needed for Problem #4
  char delete01[] = "1703";
  char delete02[] = "1358";    
	char delete03[] = "1601";
  deleteDict(&myDic, delete01);
  deleteDict(&myDic, delete02);
  deleteDict(&myDic, delete03);
  displayOpenDict(myDic);
  displayVHeap(VH);
	
 
//Function Calls for Problem #4	    
    
    

/*------------------------------------------------------------------------------------
 * 	Problem #5 :: 1) Converts the Open Hash Dictionary into a Closed Hash Dictionary *
 *                2) Displays the Closed Hash Dictionary                             * 
 *                3) Displays the virtual heap                                       *
 *---------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #5:: ");
    printf("\n------------");
    //Declare variables needed for Problem #5
    closeDic *myCloseD = convertToCloseDict(&myDic);
    
    
    //Function Calls for Problem #5
    displayCloseDict(*myCloseD);
    displayVHeap(VH);

	 
	

	return 0;
}

/************************************************************
 *  Problem 1:: Function Definitions                          *
 ************************************************************/
 void initVHeap(VHeap *V)
 {
 	int indx;
  for (indx = 0; indx < VH_SIZE; indx++) {
    strcpy(V->VH_node[indx].elem.prodID, "    ");
    V->VH_node[indx].next = indx - 1;
  }

  V->avail = VH_SIZE - 1;
 }

cursorSet initCursorSet(VHeap *VH)
{
  cursorSet temp;
  temp.elemIndex = -1;
  temp.count = 0;
  temp.VHptr = VH;

  return temp;
}

void displayVHeap(VHeap V)
{
	//Variable Declaration here
	int i,j;

    printf("\n\nDetails of the Virtual Heap :: ");
    printf("\n------------------------------");
    printf("\nAvailable Index  ::  %d", V.avail);       //Complete this statement
	  printf("\nVHeap Address    ::  %p" , &V.VH_node);       //Complete this statemet
	
    printf("\n\n%10s", "Index");
    printf("%10s", "Prod ID");
    printf("%15s", "Next Field");
	  printf("\n%10s%10s%15s", "-----", "-------","----------");	
     
    //Write your code here 
	 for(i=0; i<VH_SIZE; i++){
    printf("\n%10d", i);
    printf("%10s", V.VH_node[i].elem.prodID);
    printf("%15d", V.VH_node[i].next);
	 }
	 

	printf("\n\n"); system("Pause");
}

void displaySet(cursorSet A)
{
	int x;
	product p;
	
	printf("\n\nDetails of the Set :: ");
	printf("\n---------------------");
	printf("\nNo. of elements ::  %d", A.count ); //Complete this code
  printf("\nElem index: %d\n", A.elemIndex);      
	printf("\n\n%-7s", "ID");
	printf("%-12s","Choco Name");
	printf("%-15s","Choco Weight");
	printf("%-10s","VHeap Index");
	printf("\n%-7s%-12s%-15s%-10s", "--", "----------", "------------", "-----------");

	//Write your code here
  int trav;
  for (trav = A.elemIndex; trav != -1; trav = A.VHptr->VH_node[trav].next) {
    printf("\n%-7s", A.VHptr->VH_node[trav].elem.prodID);
    printf("%-12s", A.VHptr->VH_node[trav].elem.prodDesc.name);
    printf("%-15d", A.VHptr->VH_node[trav].elem.prodDesc.weight);
    printf("%-10d", trav);
  }

	printf("\n\n"); system("Pause");	
}


/************************************************************
 *  Problem 2:: Function Definitions                         *
 ************************************************************/
int mallocInVHeap(VHeap *VH)
{
 int retVal = VH->avail;
 if (retVal != -1) {
  VH->avail = VH->VH_node[retVal].next;
 }
 return retVal;
}


void insertSorted(cursorSet *A, product P)
{
 	int *trav;
  // int *holder;
  for (trav = &A->elemIndex; *trav != -1 && strcmp(A->VHptr->VH_node[*trav].elem.prodID, P.prodID) < 0; trav = &A->VHptr->VH_node[*trav].next) {}
    if (strcmp(A->VHptr->VH_node[*trav].elem.prodID, P.prodID) != 0) {
      int space = mallocInVHeap(A->VHptr);
      if (space != -1) {
        A->VHptr->VH_node[space].elem = P;
        A->VHptr->VH_node[space].next = *trav;
        *trav = space;
        A->count++;
      } else {
        printf("\nNo available space. Product with ID: %s cannot be inserted", P.prodID);
      }
    } else {
        printf("\nProduct with ID: %s already exists in the set", P.prodID);
    }

  // for (trav = &A->elemIndex; *trav != -1; trav = &A->VHptr->VH_node[*trav].next) {
  //   if (strcmp(A->VHptr->VH_node[*trav].elem.prodID, P.prodID) > 0) {
  //     holder = trav;
  //   }
  // }

  // for (trav = &A->elemIndex; *trav != -1; trav = A->VHptr->VH_node[*trav].next) {}
  // if (*trav != -1) {
  //   for(trav = &A->elemIndex; *trav != -1 && strcmp(A->VHptr->VH_node[*trav].elem.prodID, P.prodID) < 0; trav = &A->VHptr->VH_node[*trav].next) {}

  // }
}

void populateSet(cursorSet *A)
{
	const int COUNT = 15;
	product data[] = { 	{"1701", {"Toblerone", 135}, 150.75, 20},
						{"1356", {"Ferrero", 200}, 250.75, 85},
						{"1109", {"Patchi", 50}, 99.75, 35},
						{"1550", {"Cadbury", 120}, 200.00, 30},
						{"1807", {"Mars", 100}, 150.75, 20},
						{"1201", {"Kitkat", 50}, 97.75, 40},
						{"1450", {"Ferrero", 100},150.50, 50},
						{"1701", {"Toblerone", 50}, 90.75, 80},
						{"1601", {"Meiji", 75}, 75.50, 60},
						{"1310", {"Nestle", 100}, 124.50, 70},
						{"1807", {"Valor", 120}, 149.50, 90},
						{"1455", {"Tango", 75}, 49.50, 100},
						{"1703", {"Toblerone", 100}, 125.75, 60},
						{"1284", {"Lindt", 100}, 250.75, 15},
						{"1688", {"Guylian", 50}, 99.75, 35},
					
		              };
    //Inserts each element of the array to the cursor set
    //Write your code here!!
    int indx;
    for (indx = 0; indx < COUNT; indx++) {
      insertSorted(A, data[indx]);
    }
}



/************************************************************
 *  Problem 3:: Function Definitions                        *
 ************************************************************/
int openHash(char * prodID)               
{ 
    int sum = 0, indx;
    for (indx = 0; prodID[indx] != '\0'; indx++) {
      sum += prodID[indx] - '0';
    }

    return sum % OPEN_DSIZE;
}


openDic initOpenDict(VHeap *VH)
{
  openDic temp;
  int indx;
  for (indx = 0; indx < OPEN_DSIZE; indx++) {
    temp.header[indx] = -1;
  }
  temp.count = 0;
  temp.dicVHptr = VH;

  return temp;
}

openDic convertToOpenDict(cursorSet *A)
{ 
  openDic open = initOpenDict(A->VHptr);
  int trav;
    for (; A->elemIndex != -1;) {
    int hashIndx = openHash(A->VHptr->VH_node[A->elemIndex].elem.prodID);
    int *travGroup;
    for (travGroup = &open.header[hashIndx]; *travGroup != -1; travGroup = &A->VHptr->VH_node[*travGroup].next) {}
    int temp = A->VHptr->VH_node[A->elemIndex].next;
    A->VHptr->VH_node[A->elemIndex].next = *travGroup;
    *travGroup = A->elemIndex;
    A->elemIndex = temp;
    open.count++;
    A->count--;
  }
  return open;
}



void displayOpenDict(openDic D)
{
	//Variable declaration here 
	
	printf("\n\nDetails of the Open Hash Dictionary:: ");
	printf("\n-------------------------------------");
	
	printf("\nNo. of elements :: %d", D.count);
	printf("\n\n%-7s", "GROUPS");
	printf("%15s","ID Numbers");
	printf("\n%-7s%15s", "------","----------");
	
	//Write your code here
  int indx;
  for (indx = 0; indx < OPEN_DSIZE; indx++) {
    int trav;
    printf("\n%-7s[%d] :: ", "Groups", indx);
    for (trav = D.header[indx]; trav != -1; trav = D.dicVHptr->VH_node[trav].next) {
      printf("%s\t", D.dicVHptr->VH_node[trav].elem.prodID);
    }
  }
	

    printf("\n\n"); system("Pause");	
}


/************************************************************
 *  Problem 4:: Function Definitions                        *
 ************************************************************/
void freeInVHeap(VHeap *VH, int ndx)
{
  strcpy(VH->VH_node[ndx].elem.prodID, "    ");
  VH->VH_node[ndx].next = VH->avail;
  VH->avail = ndx;
}

void deleteDict(openDic *D, char *IDen)
{
 int hashIndx = openHash(IDen);
 int *trav;
 for (trav = &D->header[hashIndx]; *trav != -1 && strcmp(D->dicVHptr->VH_node[*trav].elem.prodID, IDen) != 0; trav = &D->dicVHptr->VH_node[*trav].next) {}
 if (*trav != -1) {
  int temp = *trav;
  *trav = D->dicVHptr->VH_node[temp].next;
  freeInVHeap(D->dicVHptr, temp);
  printf("\nProduct with ID: %s is successfully deleted.", IDen);
 } else {
  printf("\nProduct with ID: %s is not in the dictionary", IDen);
 }
}


 /************************************************************
 *  Problem 5:: Function Definitions                        *
 ************************************************************/
int closeHash(char *ID)
{
  int sum = 0, indx;
  for (indx = 0; ID[indx] != '\0'; indx++) {
    sum += ID[indx] - '0';
  }
  return sum % CLOSE_DSIZE;  
}



void initCloseDict(closeDic CD)
{
	 int indx;
   for (indx = 0; indx < CLOSE_DSIZE; indx++) {
    strcpy(CD[indx].prodID, "EMPTY");
   }

}
 
closeDic * convertToCloseDict(openDic *D)
{
  int indx;
  closeDic *closeD = (closeDic*)malloc(sizeof(closeDic));
  if (*closeD != NULL) {
    initCloseDict(*closeD);
    List temp;
    temp.last = -1;
    for (indx = 0; indx < OPEN_DSIZE; indx++) {
        int *trav;
        for (trav = &D->header[indx]; *trav != -1;) {
            int hashIndx = closeHash(D->dicVHptr->VH_node[*trav].elem.prodID);
            if (strcmp((*closeD)[hashIndx].prodID, "EMPTY") == 0) {
                (*closeD)[hashIndx] = D->dicVHptr->VH_node[*trav].elem;
            } else {
                temp.prod[++temp.last] = D->dicVHptr->VH_node[*trav].elem;
            }
            int temp = *trav;
            *trav = D->dicVHptr->VH_node[temp].next;
            freeInVHeap(D->dicVHptr, temp);
        }
    }

    for (indx = 0; indx <= temp.last; indx++) {
        int hashIndx = closeHash(temp.prod[indx].prodID);
        int i;
        for (i = 0; strcmp((*closeD)[hashIndx].prodID, "EMPTY") != 0 && i < CLOSE_DSIZE; i++, hashIndx = ((closeHash(temp.prod[indx].prodID)) + i) % CLOSE_DSIZE) {}
        if (i != CLOSE_DSIZE) {
            (*closeD)[hashIndx] = temp.prod[indx];
        } 
    }
  }
  return closeD;
}	

void displayCloseDict(closeDic CD)
{
 	//Variable declaration here
 	
 	
	printf("\n\nDetails of Closed Hash Dictionary :: ");
	printf("\n-------------------------------------");
	printf("\n\n%-6s", "Index");
	printf("%-10s", "ChocoID");
	printf("%-15s", "Choco Name");
	printf("\n%-6s%-10s%-15s", "-----", "-------", "----------"); 
	
	//Write your code here
  int indx;
  for (indx = 0; indx < CLOSE_DSIZE; indx++) {
    printf("\n%-6d", indx);
    printf("%-10s", CD[indx].prodID);
    printf("%-15s", CD[indx].prodDesc.name);
  }
	 
	
	printf("\n\n"); system("Pause");
 
}
 
