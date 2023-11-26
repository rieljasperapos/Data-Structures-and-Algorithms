#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10

typedef int BST;

typedef struct {
    int year;
    char brand[20];
    char model[20];
    char make[20];
} carType;

typedef struct {
    carType car;
    int LC;
    int RC;
} carNode;

typedef struct {
    carNode heap[MAX];
    int avail;
} virtualHeap;

virtualHeap initVheap();
int allocSpace(virtualHeap *VH);
int deallocSpace(virtualHeap *VH, int index);
void insertCar(virtualHeap *VH, BST *L, carType car);
carType newCar(int year, char *brand, char *model, char* make);
void visualizeVheap(virtualHeap VH);


int main() {
    virtualHeap myVH = initVheap();
    BST LIST = -1;
    visualizeVheap(myVH);
    insertCar(&myVH, &LIST, newCar(2016, "Hyundai", "Accent", "Hyundai"));
    insertCar(&myVH, &LIST, newCar(2019, "Toyota", "Wigo", "Toyota"));
    insertCar(&myVH, &LIST, newCar(2013, "Toyota", "Avanza", "Toyota"));
    insertCar(&myVH, &LIST, newCar(2015, "Toyota", "Raize", "Toyota"));

    printf("\n\n");

    visualizeVheap(myVH);


}

carType newCar(int year, char *brand, char *model, char* make) {
    carType Car;
    Car.year = year;
    strcpy(Car.make, make);
    strcpy(Car.brand, brand);
    strcpy(Car.model, model);

    return Car;
}

virtualHeap initVheap() {
    virtualHeap retHeap;
    int indx;
    for (indx = 0; indx < MAX; indx++) {
        strcpy(retHeap.heap[indx].car.make, "EMPTY");
        strcpy(retHeap.heap[indx].car.brand, "EMPTY");
        strcpy(retHeap.heap[indx].car.model, "EMPTY");
        retHeap.heap[indx].car.year = -1;
        retHeap.heap[indx].LC = indx - 1;
        retHeap.heap[indx].RC = indx - 1;
    }

    retHeap.avail = MAX - 1;

    return retHeap;
}

int allocSpace(virtualHeap *VH) {
    int retVal = VH->avail;
    if (retVal != -1) {
        VH->avail = VH->heap[retVal].LC;
    }

    return retVal;
}

void insertCar(virtualHeap *VH, BST *L, carType car) {
    int index = allocSpace(VH);
    while (*L != -1) {
        if (car.year < VH->heap[*L].car.year) {
            L = &(VH->heap[*L].LC);
        } else if (car.year > VH->heap[*L].car.year) {
            L = &(VH->heap[*L].RC);
        }
    }
    VH->heap[index].car = car;
    VH->heap[index].LC = -1;
    VH->heap[index].RC = -1;
    *L = index;

}

void visualizeVheap(virtualHeap VH) {
    int indx;
    for (indx = 0; indx < MAX; indx++) {
        printf("%s %10s %10s %10s %10s %10s\n", "MAKE", "BRAND", "MODEL", "YEAR", "LC", "RC");
        printf("%s %10s %10s %10d %10d %10d\n", VH.heap[indx].car.make, VH.heap[indx].car.brand, VH.heap[indx].car.model, VH.heap[indx].car.year, VH.heap[indx].LC, VH.heap[indx].RC);
    }
}

