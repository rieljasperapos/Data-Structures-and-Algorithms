#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXORDERS 20
#define CUSTBUCKETS 10

int lastOrderNumber = 10000;

typedef enum{OPEN, CLOSED} orderStatus;  //used in Closed Hashing of Orders
typedef enum{PREPARING, SERVED} pizzaStatus;
typedef unsigned char toppingsCW;       //Computer Word representation of toppings
typedef int toppingsBW[8];              //Bit Vector representation of toppings

typedef struct{
    char pizzaName[32];
    toppingsBW pizzaToppings;
}pizzaType;

typedef struct pizzaNode{
    pizzaType P;
    pizzaStatus pStat;                  //PREPARING by default
    struct pizzaNode* nextPizza;
}pizzaNode, *pizzaList;

typedef struct{
    char fName[64];
    char lName[32];
}nameDetails;

typedef struct{
    char customerID[9];
    nameDetails custName;
}customer;

typedef struct customerNode{
    customer C;
    struct customerNode* nextCust;
}customerNode, *custList;

typedef custList cDict[CUSTBUCKETS];    //Open Hashing Representation of Customers

typedef struct{
    int orderNumber;
    customer cust;
    pizzaList pList;
    orderStatus stat;                   //OPEN by default
}orderType;

typedef struct{
    orderType orderList[MAXORDERS];
    int numOrders;
}orderList;                             //Closed Hashing Representation of Orders

void createCustomerFile(void)
{
    customer customers[] = {
            {"CUST001", {"SEAN ANSELMO", "ABELLANA"}},
            {"CUST002", {"VICTOR", "AGUHOB"}},
            {"CUST003", {"YEVGENY GRAZIO MARI", "ALBAÑO"}},
            {"CUST004", {"MIGUEL CARLOS", "BERINGUEL"}},
            {"CUST005", {"KARYLLE", "BERNATE"}},
            {"CUST006", {"RAYNOR", "BUHIAN"}},
            {"CUST007", {"NIÑO JAN", "CABATAS"}},
            {"CUST008", {"KENNETH JOHN", "CANTILLAS"}},
            {"CUST009", {"VINCEADE", "CENTINO"}},
            {"CUST010", {"JUN", "CHEONG"}},
            {"CUST011", {"CERIL", "HEYROSA"}},
            {"CUST012", {"JEREMIAH JACOB ANTHONY", "JUINIO"}},
            {"CUST013", {"JIWOO", "JUNG"}},
            {"CUST014", {"XANDER JACOB", "LABIDE"}},
            {"CUST015", {"ACHILLE LORENZO", "LANUTAN"}},
            {"CUST016", {"MATT VINCENT", "MAGDADARO"}},
            {"CUST017", {"GREGG ALEXANDER", "MARAYAN"}},
            {"CUST018", {"JASPER LEE", "MARBELLA"}},
            {"CUST019", {"DAN LIUS", "MONSALES"}},
            {"CUST020", {"SHAWN RYAN", "NACARIO"}},
            {"CUST021", {"SHANNEN", "NAZARENO"}},
            {"CUST022", {"OIEU ZHYDD", "NUÑEZA"}},
            {"CUST023", {"MARC NELSON", "OCHAVO"}},
            {"CUST024", {"RAY EMANUEL", "PATALINGHUG"}},
            {"CUST025", {"NATHAN ELDRIDGE MITNICK", "PERNITES"}},
            {"CUST026", {"LANCE JUSTIN", "RAMOS"}},
            {"CUST027", {"KENT JOSEPH", "RICONALLA"}},
            {"CUST028", {"JOSHUA LOUI", "SOQUEÑO"}},
            {"CUST029", {"ASHLENGAIL", "VICTOR"}},
            {"CUST030", {"MURLIWANI", "GANGARAM"}}
        };
        FILE* file = fopen("customersTest.txt", "w");
        if (file != NULL) {
            // for (int i = 0; i < sizeof(customers) / sizeof(customers[0]); i++) {
            //     fwrite(&customers[i], sizeof(customer), 1, file);
            // }
            fwrite(&customers, sizeof(customer), sizeof(customers) / sizeof(customers[0]), file);
        }
        fclose(file);
}

/*
 initCustomerDict() = This function will receive as parameter a cDict, which is an array of custList (Linked List of Customers). 
 The function will initialize the dictionary by setting each element in cDict to be empty.
 */
void initCustomerDict(cDict customers)
{
    int indx;
    for (indx = 0; indx < CUSTBUCKETS; indx++) {
      customers[indx] = NULL;
    }
}

/*
 hashCustomer() = This function will receive as a parameter a customerID. 
 The function will add up the first 3 digits in the customerID and let the remainder of the sum when divided by 10 be returned to the calling function.
 */
int hashCustomer(char customerID[])
{
    int retVal;
    int sum = 0;
    int indx;
    for (indx = strlen(customerID) - 1; indx > 3; indx--) {
      sum += customerID[indx] - '0';
    }
    retVal = sum % 10;
    
    return retVal;
}

/*
 addNewCustomer() = This function will add a new customer to the cDict given a customer record. 
 The function will only add the customer if the customer does not yet exist. Also, the customer is inserted into its proper "bucket" 
 (linked list at index N based on hash). The new customer should be inserted in its proper place in the list, sorted ascending by family name.
 */
void addNewCustomer(cDict customers, customer C)
{
    int hashIndx = hashCustomer(C.customerID);
    custList *trav;
    for (trav = &customers[hashIndx]; *trav != NULL && strcmp((*trav)->C.custName.lName, C.custName.lName) < 0; trav = &(*trav)->nextCust) {}
    if (*trav == NULL || strcmp((*trav)->C.customerID, C.customerID) != 0) {
      custList temp = (custList)malloc(sizeof(customerNode));
      if (temp != NULL) {
        temp->C = C;
        temp->nextCust = *trav;
        *trav = temp;
      }
    }
}

/*
 populateCustomers() = This function will read a file "customers.txt", and populate the given cDict with the customer records in the file. 
 You may use the previously written functions for this function.
 */
void populateCustomers(cDict customers) {
  FILE *fp;
  customer customer;
  fp = fopen("customersTest.txt", "r");
  if (fp != NULL) {
    while(fread(&customer, sizeof(customer), 1, fp)) {
      addNewCustomer(customers, customer);
    }
  }

  fclose(fp);
}

/*
 buildPizza() = This function will receive as parameter a pizzaName, and a list of toppings represented in computer word. 
 Each bit in the CW representation represent the ff:
        0000 0000
        8765 4321
    1 - Pepperoni
    2 - Ham
    3 - Onions
    4 - Pineapples
    5 - Bacon
    6 - Olives
    7 - Bell Peppers
    8 - Mushrooms
    
    For example: A Hawaiian Pizza with mushrooms, pineapples, and pepperoni is represented as: 1000 1001.
 
    Once the pizza record has been built, return it to the calling function.
 */
pizzaType buildPizza(char pizzaName[], toppingsCW toppings)
{
    pizzaType retVal;
    strcpy(retVal.pizzaName, pizzaName);
    int tops[8];
    int size = sizeof(char) * 8;
    int indx;
    for (indx = size - 1; indx >= 0; indx--) {
      if ((toppings & 1 << indx) > 0) {
        retVal.pizzaToppings[indx] = 1;
      } else {
        retVal.pizzaToppings[indx] = 0;
      }
    }
    
    return retVal;
}

/*
 hashOrder() = The function will receive an orderID as parameter. The function will take the last 4 digits of the orderID, 
 and return the remainder when it is divided by 20.
 */

int hashOrder(int orderID)
{
    int retVal;
    int extracted4Dig = orderID % 10000;
    retVal = extracted4Dig % 20;
    
    return retVal;
}

/*
 orderPizza() = This function will receive an orderList, a cDict, a customerID, and a pizza to order. 
 The function will add a new order to the orderList for the given customerID and pizza record. Update any fields as necessary. 
 Only add the order if the customer exists. Resolve any collisions using linear probing.
 */

void orderPizza(orderList* orders, cDict customers, char customerID[], pizzaType pizza, int orderID)
{
    int hashCustomerIndx = hashCustomer(customerID);
    custList trav;
    for (trav = customers[hashCustomerIndx]; trav != NULL && strcmp(trav->C.customerID, customerID) != 0; trav = trav->nextCust) {}

    if (trav != NULL) {
      int hashOrderIndx = hashOrder(orderID);
      int indx;
      for (indx = 0;
          strcmp(orders->orderList[hashOrderIndx].cust.customerID, "EMPTY") != 0 && strcmp(orders->orderList[hashOrderIndx].cust.customerID, customerID) != 0 && indx < MAXORDERS;
          indx++, hashOrderIndx = (hashOrder(orderID) + indx) % MAXORDERS) {}

      if (indx != MAXORDERS) {
        orders->orderList[hashOrderIndx].cust = trav->C;
        orders->orderList[hashOrderIndx].orderNumber = orderID;
        pizzaList temp = (pizzaList)malloc(sizeof(pizzaNode));
        if (temp != NULL) {
          temp->P = pizza;
          temp->pStat = PREPARING;
          temp->nextPizza = orders->orderList[hashOrderIndx].pList;
          orders->orderList[hashOrderIndx].pList = temp;
        }
        orders->numOrders++;
      }
    }
}

/*
 servePizza() = This function will receive an orderList, an orderNumber and a pizzaName. 
 The function will go through the given orderList and the pizzas for the specified orderNumber. If the pizza exists, 
 then update the pizzaStatus to be SERVED.
 */
void servePizza(orderList* orders, int orderNumber, char pizzaName[])
{
    int hashOrderIndx = hashOrder(orderNumber);
    pizzaList trav;
    for (trav = orders->orderList[hashOrderIndx].pList; trav != NULL && strcmp(trav->P.pizzaName, pizzaName) != 0; trav = trav->nextPizza) {}
    if (trav != NULL) {
      trav->pStat = SERVED;
    }
}

/*
 updateOrderStatus() = This function will receive an orderList and an orderID. 
 The function will go through the list of pizzas in the order record of the given orderID, and check if all of the pizzas have been SERVED. 
 If they have all been SERVED, then the function will update the orderStatus to CLOSED.
 */
void updateOrderStatus(orderList* orders, int orderNumber)
{
  int hashOrderIndx = hashOrder(orderNumber);
  pizzaList trav;
  for (trav = orders->orderList[hashOrderIndx].pList; trav != NULL && trav->pStat == SERVED; trav = trav->nextPizza) {}
  if (trav == NULL) {
    orders->orderList[hashOrderIndx].stat = CLOSED;
  }
}

/*
 displayOrderList() = This function will go through each order in the orderList and display each of the orders in the ff: format:
 
    OrderNumber:
    Customer ID:
    Customer Name:
    Pizza Orders: pizzaName1(SERVED) -> pizzaName2(PREPARING)
    Order Status:
 */

void displayOrderList(orderList orders)
{
    int indx;
    for (indx = 0; indx < MAXORDERS; indx++) {
      printf("OrderNumber: %d\n", orders.orderList[indx].orderNumber);
      printf("Customer ID: %s\n", orders.orderList[indx].cust.customerID);
      printf("Customer Name: %s %s\n", orders.orderList[indx].cust.custName.fName, orders.orderList[indx].cust.custName.lName);
      printf("Pizza Orders: ");
      while (orders.orderList[indx].pList != NULL) {
        printf("%s", orders.orderList[indx].pList->P.pizzaName); 
        (orders.orderList[indx].pList->pStat == PREPARING) ? printf("(PREPARING) ") : printf("(SERVED) ");
        orders.orderList[indx].pList = orders.orderList[indx].pList->nextPizza;
      }
      printf("\nOrder Status: ");
      orders.orderList[indx].stat == OPEN ? printf("OPEN\n") : printf("CLOSE\n");
      printf("\n\n");
    }
}

void displayCustomerList(cDict customers) {
  int indx;
  for (indx = 0; indx < CUSTBUCKETS; indx++) {
    printf("Customer[%d]: ", indx);
    while (customers[indx] != NULL) {
      printf("%s ", customers[indx]->C.customerID);
      customers[indx] = customers[indx]->nextCust;
    }
    printf("\n");
  }
}

int main(void)
{
	createCustomerFile();
  cDict myCust;
  initCustomerDict(myCust);
  populateCustomers(myCust);
  displayCustomerList(myCust);

  // orderList customerOrders;
  // int indx;
  // for (indx = 0; indx < MAXORDERS; indx++) {
  //   customerOrders.orderList[indx].pList = NULL;
  //   strcpy(customerOrders.orderList[indx].cust.customerID, "EMPTY");
  //   strcpy(customerOrders.orderList[indx].cust.custName.fName, "   ");
  //   strcpy(customerOrders.orderList[indx].cust.custName.lName, "   ");
  //   customerOrders.orderList[indx].stat = OPEN;
  //   customerOrders.orderList[indx].orderNumber = 0;
  // }
  // customerOrders.numOrders = 0;

  // pizzaType pizzaOrder = buildPizza("Hawaiian", 137);
  // pizzaType pizzaOrder1 = buildPizza("Beef and Mushroom", 137);
  // pizzaType pizzaOrder2 = buildPizza("All Pepperoni", 137);
  // pizzaType pizzaOrder3 = buildPizza("All Cheese", 137);
  // orderPizza(&customerOrders, myCust, "CUST001", pizzaOrder, 12312);
  // orderPizza(&customerOrders, myCust, "CUST023", pizzaOrder, 46789);
  // orderPizza(&customerOrders, myCust, "CUST023", pizzaOrder1, 46789);
  // orderPizza(&customerOrders, myCust, "CUST023", pizzaOrder2, 46789);
  // orderPizza(&customerOrders, myCust, "CUST023", pizzaOrder3, 46789);
  // servePizza(&customerOrders, 46789, pizzaOrder.pizzaName);
  // servePizza(&customerOrders, 46789, pizzaOrder1.pizzaName);
  // servePizza(&customerOrders, 46789, pizzaOrder2.pizzaName);
  // servePizza(&customerOrders, 46789, pizzaOrder3.pizzaName);
  // // servePizza(&customerOrders, 46789, "Beef and Mushroom");
  // updateOrderStatus(&customerOrders, 46789);
  
  // displayOrderList(customerOrders);
    return 0;
}
