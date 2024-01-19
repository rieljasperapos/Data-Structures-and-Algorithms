#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLOSE_DSIZE 0XF    //size of Close Hash Table
#define SET_SIZE   0XC    //size of the array implementation of Set
/******************************************************************************
 * Data Structure Definition:                                                 *
 ******************************************************************************/
typedef struct {  
	char name[24];          // Chocolate name  
 	int  weight;            // Chocolate weight in grams  
} chocoDesc;

typedef struct {
  char prodID[8];          //  product ID uniquely identifies the products; EMPTY or DELETED   
  chocoDesc prodDesc;      //  product description 
 	float prodPrice;         //  product price 
  int prodQty;             //  product count or quantity   
} product;                   //  product record  

typedef struct pSet {
	product prod[SET_SIZE];
	int last;          //index of the last element; -1 if list is empty	
} ProdSet;

/**********************************************
 * Closed Hashing with 2 pass loading          *
 **********************************************/
#define EMPTY   "empty"         // stored in product ID field  
#define DELETED  "deleted"      // stored in product ID field * 

typedef product closeDic[CLOSE_DSIZE];   //Definition of the closed hash dictionary
  
/**********************************************************
 * Function Prototypes                                    *
 *********************************************************/
ProdSet populateProdSet();

int closeHash(char *ID);     
void initCloseDict(closeDic CD);
closeDic * createCloseDict(ProdSet S);	
void displayCloseDict(closeDic CD);

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
int main( ) 
{	
/*------------------------------------------------------------------------------------
 * 	Problem #2  :: 1) Populate the set by calling populateProdSet                  *
 *                   2) Calls createCloseDict()                                     *
 *---------------------------------------------------------------------------------*/	
	printf("\n\n\nProblem #2 :: ");
  printf("\n------------");
    
  //Write your code here
  ProdSet mySet = populateProdSet();
  closeDic *myCD;
  myCD = createCloseDict(mySet);

	return 0;
}

/************************************************************
 *  Problem  :: Function Definitions                          *
 ************************************************************/
ProdSet populateProdSet()
{ 
  product data[] = { 	
            {"1701", {"Toblerone", 135}, 150.75, 20}, {"1356", {"Ferrero", 200}, 250.75, 85},
						{"1109", {"Patchi", 50}, 99.75, 35}, {"1550", {"Cadbury", 120}, 200.00, 30},
						{"1807", {"Mars", 100}, 150.75, 20}, {"1201", {"Kitkat", 50}, 97.75, 40},
						{"1450", {"Ferrero", 100},150.50, 50}, {"1601", {"Meiji", 75}, 75.50, 60},
						{"1310", {"Nestle", 100}, 124.50, 70}, {"1455", {"Tango", 75}, 49.50, 100},
						{"1703", {"Toblerone", 100}, 125.75, 60}, {"1284", {"Lindt", 100}, 250.75, 15},
						{"1688", {"Guylian", 50}, 99.75, 35}, {"1107", {"Valor", 120}, 149.50, 90}
	};
  int count = sizeof(data)/sizeof(data[0]);
  
  ProdSet Set = {.last = SET_SIZE - 1};
	memcpy(Set.prod, data, sizeof(data[0]) * SET_SIZE);

  return Set;  
}

int closeHash(char *ID)
{
    //Write your code here
    int indx, sum = 0;
    for (indx = 0; ID[indx] != '\0'; indx++) {
      int digit = ID[indx] - '0';
      sum += digit;
    }

    return sum % CLOSE_DSIZE;
} 

void initCloseDict(closeDic CD)
{
    //Write your code here
    int indx;
    for (indx = 0; indx < CLOSE_DSIZE; indx++) {
      strcpy(CD[indx].prodID, EMPTY);
    }
}

closeDic * createCloseDict(ProdSet L)
{
  closeDic *temp = malloc(sizeof(closeDic));
  ProdSet tempSet;
  int count = 0;
  initCloseDict(*temp);
  
	// Uncomment these lines and put before a call to displayCloseDict()
  printf("\n\n----- Empty Dictionary ------");
  displayCloseDict(*temp);

	//Write your code here 
  int indx;
  for (indx = 0; indx < SET_SIZE; indx++) {
    int hashIndx = closeHash(L.prod[indx].prodID);
    printf("HASHINDEX OF %s: %d\n", L.prod[indx].prodID, hashIndx);
    if (strcmp((*temp)[hashIndx].prodID, EMPTY) == 0) {
      (*temp)[hashIndx] = L.prod[indx];
    } else {
      tempSet.prod[count++] = L.prod[indx];
    }
  }

  printf("\n\n----- Dictionary without the Synonyms ------");
  displayCloseDict(*temp);

  for (indx = 0; indx < count; indx++) {
    int hashIndx = closeHash(tempSet.prod[indx].prodID);
    for (int i = 0; strcmp((*temp)[hashIndx].prodID, EMPTY) != 0; i++) {
      hashIndx = (closeHash(tempSet.prod[indx].prodID) + i) % CLOSE_DSIZE;
    }
    (*temp)[hashIndx] = tempSet.prod[indx];
  }

  printf("\n\n----- Dictionary with ALL the Synonyms -----");
  displayCloseDict(*temp);


  return temp;
}	

void displayCloseDict(closeDic CD)
{
	printf("\n\n%-6s", "Index");
	printf("%-10s", "ChocoID");
	printf("%-15s", "Choco Name");
	printf("\n%-6s%-10s%-15s", "-----", "-------", "----------"); 
	
	//write your code here!!
  int indx;
  for (indx = 0; indx < CLOSE_DSIZE; indx++) {
    printf("\n%-6d", indx);
    printf("%-10s", CD[indx].prodID);
    printf("%-15s", CD[indx].prodDesc.name);
  }

	printf("\n\n"); system("Pause");  //keep this statement

}

