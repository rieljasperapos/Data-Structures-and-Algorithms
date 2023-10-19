/******************************************************************
 * Project Name:  List, Set and Dictionary                        *
 * Programmer  :  							                         *
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
	VHeap myVH;
	cursorSet A;

 	//Function Calls for Problem #1
	initVHeap(&myVH);
	A = initCursorSet(&myVH);

	displayVHeap(myVH);
	displaySet(A);
	


/*---------------------------------------------------------------------------------
 * 	Problem #2 ::  1) Populates the Cursor set which is sorted in ascending order *
 *                    according to ID                                             *
 *                 2) Displays the Cursor set                                     * 
 *--------------------------------------------------------------------------------*/	 
	printf("\n\n\nProblem #2:: "); 
	printf("\n------------");
	//Declare variables needed for Problem #2

	
 	//Function Calls for Problem #2
	populateSet(&A);
	displaySet(A);

	
/*---------------------------------------------------------------------------------
 * 	Problem #3 ::  1) Converts the Cursor set into an Open Hash Dictionary        *      
 *                 2) Displays the Open Hash Dictionary                           *
 *                 3) Displays the empty Cursor set.                              * 
 *--------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #3:: "); 
	printf("\n------------");
	//Declare variables needed for Problem #3
	openDic myDictionary;

 	//Function Calls for Problem #3
	displayVHeap(myVH);
	myDictionary = convertToOpenDict(&A);
	displayOpenDict(myDictionary);
	displayVHeap(myVH);
	displaySet(A);

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

//Function Calls for Problem #4
	deleteDict(&myDictionary, delete01);
	deleteDict(&myDictionary, delete02);
	deleteDict(&myDictionary, delete03);
	displayOpenDict(myDictionary);
	displayVHeap(myVH);
    
    

/*------------------------------------------------------------------------------------
 * 	Problem #5 :: 1) Converts the Open Hash Dictionary into a Closed Hash Dictionary *
 *                2) Displays the Closed Hash Dictionary                             * 
 *                3) Displays the virtual heap                                       *
 *---------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #5:: ");
    printf("\n------------");
    //Declare variables needed for Problem #5
	closeDic *myCloseDic;
	myCloseDic = convertToCloseDict(&myDictionary);
	displayCloseDict(*myCloseDic);
	displayVHeap(myVH);

    
    
    //Function Calls for Problem #5

	

	return 0;
}

/************************************************************
 *  Problem 1:: Function Definitions                          *
 ************************************************************/
void initVHeap(VHeap *V)
{
	int indx;
	for (indx = 0; indx < VH_SIZE; indx++) {
		strcpy(V->VH_node[indx].elem.prodID, "EMPTY");
		V->VH_node[indx].next = indx-1;
	}
	
	V->avail = VH_SIZE-1;
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
	int i;

    printf("\n\nDetails of the Virtual Heap :: ");
    printf("\n------------------------------");
    printf("\nAvailable Index  ::  %d", V.avail);       //Complete this statement
	printf("\nVHeap Address    ::  %d",  &V);       //Complete this statemet
	
    printf("\n\n%10s", "Index");
    printf("%10s", "Prod ID");
    printf("%15s", "Next Field");
	printf("\n%10s%10s%15s\n", "-----", "-------","----------");	

    //Write your code here
	for (i = 0; i < VH_SIZE; i++) {
		printf("%10d", i);
		printf("%10s", V.VH_node[i].elem.prodID);
		printf("%15d\n", V.VH_node[i].next);
	}
	
    system("Pause");
}

void displaySet(cursorSet A)
{
	int x;
	product p;
	
	printf("\n\nDetails of the Set :: ");
	printf("\n---------------------");
	printf("\nNo. of elements ::  %d", A.count);      //Complete this code
	printf("\n\n%-7s", "ID");
	printf("%-12s","Choco Name");
	printf("%-15s","Choco Weight");
	printf("%-10s","VHeap Index");
	printf("\n%-7s%-12s%-15s%-10s\n", "--", "----------", "------------", "-----------");

	//Write your code here
	int i;
	if (A.count != 0) {
		for (i = A.elemIndex; i != -1; i = A.VHptr->VH_node[i].next) {
			printf("%-7s", A.VHptr->VH_node[i].elem.prodID);
			printf("%-12s", A.VHptr->VH_node[i].elem.prodDesc.name);
			printf("%-15d", A.VHptr->VH_node[i].elem.prodDesc.weight);
			printf("%-10d\n", i);
		}
	}
	

	system("Pause");	
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
	int *indxPtr = &(A->elemIndex);
	for (; *indxPtr != -1 && strcmp(A->VHptr->VH_node[*indxPtr].elem.prodID, P.prodID) < 0; indxPtr = &(A->VHptr->VH_node[*indxPtr].next)){}
	// printf("My index ptr is: %d\n", *indxPtr);
	if (strcmp(A->VHptr->VH_node[*indxPtr].elem.prodID, P.prodID) == 0) {
		printf("\nProduct with ID: %s already exists in the set", P.prodID);
	} else if (A->count == VH_SIZE) {
		printf("\nNo available space. Product with ID: %s cannot be inserted.\n", P.prodID);
	} else {
		int temp = mallocInVHeap(A->VHptr);
		if (temp != -1) {
			A->VHptr->VH_node[temp].elem = P;
			A->VHptr->VH_node[temp].next = *indxPtr;
			*indxPtr = temp;
			A->count++;
		}
	}

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
int openHash(char *IDen)               
{
	int total;
	int indx;
	int toInteger;
	for (indx = 0; IDen[indx] != '\0'; indx++) {
		toInteger = IDen[indx] - '0';
		total += toInteger;
	}

	return total % 10;
	
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
	openDic temp = initOpenDict(A->VHptr);
	int indx;
	int *trav;
	for (indx = 0; indx < VH_SIZE; indx++) {
		int hashIndex = openHash(A->VHptr->VH_node[indx].elem.prodID);
		printf("HashValue: %d\n", hashIndex);
		for (trav = &(temp.header[hashIndex]); *trav != -1 && strcmp(A->VHptr->VH_node[*trav].elem.prodID, A->VHptr->VH_node[indx].elem.prodID) < 0; trav = &(A->VHptr->VH_node[*trav].next)){}
		A->VHptr->VH_node[indx].next = *trav;
		*trav = indx;
		temp.count++;
		A->count--;
	}

	return temp;

}


void displayOpenDict(openDic D)
{
	//Variable declaration here 
	int count;
	
	printf("\n\nDetails of the Open Hash Dictionary:: ");
	printf("\n-------------------------------------");
	
	printf("\nNo. of elements :: %d", D.count);
	printf("\n\n%-7s", "GROUPS");
	printf("%15s","ID Numbers");
	printf("\n%-7s%15s\n", "------","----------");
	
	//Write your code here
	int i;
	int trav;
	// printf("\n");
	for (i = 0; i < OPEN_DSIZE; i++) {
		// printf("%-7s", "Group[%d] ::", i);
		printf("Group[%d] :: ", i);
		for (trav = D.header[i]; trav != -1; trav = D.dicVHptr->VH_node[trav].next) {
			// printf("trav is: %d\n", trav);
			printf("%s ", D.dicVHptr->VH_node[trav].elem.prodID);
			// printf("%15s", D.dicVHptr->VH_node[5].elem.prodID);
		}
		printf("\n");
	}
	system("Pause");

}


/************************************************************
 *  Problem 4:: Function Definitions                        *
 ************************************************************/
void freeInVHeap(VHeap *VH, int ndx)
{
	if (ndx != -1) {
		VH->VH_node[ndx].next = VH->avail;
		VH->avail = ndx;
	}
}

void deleteDict(openDic *D, char *IDen)
{
	int i;
	int *trav;
	for (i = 0; i < OPEN_DSIZE; i++) {
		for (trav = &(D->header[i]); *trav != -1 && strcmp(D->dicVHptr->VH_node[*trav].elem.prodID, IDen) != 0; trav = &(D->dicVHptr->VH_node[*trav].next)) {}
		if (*trav != -1) {
			int temp = *trav;
			*trav = D->dicVHptr->VH_node[temp].next;
			freeInVHeap(D->dicVHptr, temp);
			D->count--;
		}
	}
}


/************************************************************
 *  Problem 5:: Function Definitions                        *
 ************************************************************/

// #define EMPTY   "empty"     // stored in product ID field  
// #define DELETED  "del"      // stored in product ID field * 

// typedef product closeDic[CLOSE_DSIZE]; 

int closeHash(char *ID)
{
	int i;
	int total = 0;
	int toInteger = 0;

	for (i = 0; ID[i] != '\0'; i++) {
		toInteger = ID[i] - '0';
		total += toInteger;
	}

	return total % CLOSE_DSIZE;
}



void initCloseDict(closeDic CD)
{
	int indx;
	for (indx = 0; indx < CLOSE_DSIZE; indx++) {
		strcpy(CD[indx].prodID, EMPTY);
	}

}

closeDic * convertToCloseDict(openDic *D)
{
    closeDic *temp = malloc(sizeof(closeDic));
	if (temp != NULL) {
		initCloseDict(*temp);
	}
	
	int indx, trav, i;
	for (indx = 0; indx < OPEN_DSIZE; indx++) {
		for (trav = D->header[indx]; trav != -1; trav = D->dicVHptr->VH_node[trav].next) {
			int hashIndex = closeHash(D->dicVHptr->VH_node[trav].elem.prodID);
			printf("Hash Value of Closed Hash is: %d\n", hashIndex);
			while (strcmp((*temp)[hashIndex].prodID, EMPTY) != 0) {
				hashIndex = (hashIndex + 1) % CLOSE_DSIZE;
			}
			(*temp)[hashIndex] = D->dicVHptr->VH_node[trav].elem;
		}
	}

	return temp;
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
	printf("\n");
	int indx;
	for (indx = 0; indx < CLOSE_DSIZE; indx++) {
		printf("%-6d", indx);
		printf("%-10s", CD[indx].prodID);
		printf("%-15s\n", CD[indx].prodDesc.name);
	}

	
	printf("\n\n"); system("Pause");

}


