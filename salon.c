// Alejandro Guzman Avalos
// Professor Guha COP3502C Section 2
// Project 6: Priority Hair Salon (Binary Heaps)
// 11/26/21 - 12/05/21

// Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Definitions
#define MAXHEAPSIZE 100000
#define MAXSIZE 10

// Structures

// Stylist Data
typedef struct styData{
    char* styName;
    int cutTimes; 
} styData;

// Customer Data
typedef struct custData {
	char* custName;
	char* prefSty;
	int custTime;
	int custPoints;
	int custCutTime;
} custData;

// Heap
typedef struct heap {
    custData** list;
    int n;
} heap;

// Function Prototypes
// Data Inputs
void inputStyData(struct styData* stylists, int numSty);
void inputCustData(struct styData* stylists, struct custData* customers, int numCust, int numSty);
// Heap Functions
void init(heap* hPtr);
void freeHeap(heap *hPtr);
void insert(heap* hPtr, custData* item);
// Helper functions.
void percolateUp(heap* hPtr, int index);
void percolateDown(heap* hPtr, int index);
// Small utility functions.
int compare(custData* a, custData* b);
void swap(custData** ptrA, custData** ptrB);
// Math Functions
void calcLoyalty(struct custData* customers, int numCust);
void calcTime(struct styData* stylists, struct custData* customers, int numCust, int numSty);
// Troubleshooting Functions
void printData(struct custData* customers, struct styData* stylists, int numCust, int numSty);
// Sorting Functions
void MergeSort(int values[], int start, int end);
void Merge(int values[], int start, int middle, int end);

// Main Function
int main(){

	// Set up heap.
    heap myHeap;
    init(&myHeap);

    // Declare variables
	int i;
	int numSty, numCust;
	char styName[MAXSIZE];

	scanf("%d %d", &numCust, &numSty);
	// Checks bounds 
	if(numCust > 100000 || numSty > 10){
		printf("An input exceeds max value. Try again.\n");
		exit(0);
	}

    // Allocate memory
    struct styData* stylists = malloc(numSty*sizeof(*stylists));
    struct custData* customers = malloc(numCust*sizeof(*customers));

    inputStyData(stylists, numSty);
    inputCustData(stylists, customers, numCust, numSty);

    //Sorts customers by loyalty point priority
    //MergeSort(custData[], 0, numCust-1);

    calcLoyalty(customers, numCust);
    printData(customers, stylists, numCust, numSty);

	// Frees all the memory
    free(stylists);
    free(customers);
	freeHeap(&myHeap);

	return 0;
}

// Functions

// Initializes Heap
void init(heap* hPtr) {

    // Make enough space - make each pointer NULL.
    hPtr->list = malloc(sizeof(custData*)*(MAXHEAPSIZE+1));
    int i;
    for (i=0; i<MAXHEAPSIZE+1; i++) hPtr->list[i] = NULL;
    hPtr->n = 0;
}

void percolateUp(heap* hPtr, int index) {

    // At root, can't go up any more.
    if (index == 1) return;

    int pIndex = index/2;

    // Node and parent are out of order, swap and recurse.
    if (compare(hPtr->list[index], hPtr->list[pIndex]) < 0) {
        swap(&hPtr->list[index], &hPtr->list[pIndex]);
        percolateUp(hPtr, pIndex);
    }
}

// Percolate
void percolateDown(heap* hPtr, int index){

    // Leaf node.
    if (2*index > hPtr->n) return;

    // You only have a left child.
    if (2*index == hPtr->n) {

        // Last swap.
        if (compare(hPtr->list[2*index], hPtr->list[index]) < 0)
            swap(&hPtr->list[2*index], &hPtr->list[index]);
        return;
    }
}

// Insert
void insert(heap* hPtr, custData* item){

    // Increment the size of the heap.
    hPtr->n++;

    // Copy new item into first open slot in the heap.
    hPtr->list[hPtr->n] = item;

    // Now percolate this item up so it goes to its rightful place.
    percolateUp(hPtr, hPtr->n);
}

// Checks for Priority
int compare(custData* a, custData* b){
    if (a->custPoints != b->custPoints)
        return a->custPoints - b->custPoints;
    return strcmp(a->custName, b->custName);
}

// Free Heap
void freeHeap(heap* hPtr) {
    free(hPtr->list);   
}

// Swap
void swap(custData** ptrA, custData** ptrB) {
    custData* tmp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = tmp;
}

// Input Stylist Data
void inputStyData(struct styData* stylists, int numSty){

    int i;

    for(i=0; i<numSty; i++){
        // Allocate memory for stylist name
        stylists[i].styName=(char*)malloc(sizeof(char*));
        scanf("%s", stylists[i].styName);
    }   
}

// Input Customer Data
void inputCustData(struct styData* stylists, struct custData* customers, int numCust, int numSty){

    int i, j;
    char noneString[] = "NONE";

    for(i=0; i<numCust; i++){

        // Allocate memory for customer names and their preferred stylist
        customers[i].custName=(char*)malloc(sizeof(char*));
        customers[i].prefSty=(char*)malloc(sizeof(char*));

        scanf("%d %s %s %d %d", &customers[i].custTime, customers[i].custName, 
                                customers[i].prefSty, &customers[i].custPoints, 
                                &customers[i].custCutTime);
    }

    // If the customer typed in NONE, they will be assigned a hair stylist

    for(i=0; i<numCust; i++){
        for(j=0; j<numSty; j++){
            if(strcmp(customers[i].prefSty, noneString) == 0){
                strcpy(customers[i].prefSty, stylists[j].styName);
            }
        }
    }
}

// calcTime
void calcTime(struct styData* stylists, struct custData* customers, int numCust, int numSty){

    int i, j;

    // Calculates the total time the stylist will have worked after the store opens
    for(i=0; i<numCust; i++){
        for(j=0; j<numSty; j++){
            if(strcmp(customers[i].prefSty, stylists[j].styName) == 0){
                stylists[j].cutTimes += customers[i].custCutTime;
            }
        }
    }


}


// Calculate Loyalty
void calcLoyalty(struct custData* customers, int numCust){

    int i;

    // Calculates Loyalty Points
    for(i=0; i<numCust; i++){
        customers[i].custPoints += (customers[i].custCutTime/10); 
    }
}

// Prints all the data
void printData(struct custData* customers, struct styData* stylists, int numCust, int numSty){
    
    int i;

    printf("\n");
    // Prints all the customer data
    for(i=0; i<numCust; i++){
        printf("%s %d %d %s\n", customers[i].custName, 
                (customers[i].custCutTime + customers[i].custTime), 
                customers[i].custPoints, customers[i].prefSty);
    }

}

// Merge Sort
void MergeSort(int values[], int start, int end){

    int mid;
  
    // Check if our sorting range is more than one element.
    if (start < end) {

        mid = (start+end)/2;
    
        // Sort the first half of the values.
        MergeSort(values,start, mid);
    
        // Sort the last half of the values.
        MergeSort(values, mid+1, end);
    
        // Put it all together.
        Merge(values, start, mid+1, end);
    }
}

// Merge 
void Merge(int values[], int start, int middle, int end) {

    //printf("merge %d, %d, %d\n", start, middle, end);
    
    int *temp, i, length, count1, count2, mc;
  
    // Allocate the proper amount of space for our auxiliary array.
    length = end - start + 1;
    temp = (int*)calloc(length, sizeof(int));

    // These will be our indexes into our two sorted lists.
    count1 = start;
    count2 = middle;
  
    // Keeps track of our index into our auxiliary array.
    mc = 0;

    // Here we copy values into our auxiliary array, so long as there are 
    // numbers from both lists to copy.
    while ((count1 < middle) || (count2 <= end)) {

        // Next value to copy comes from list one - make sure list
        // one isn't exhausted yet. Also make sure we don't access index
        // count2 if we aren't supposed to.
        if (count2 > end || (count1 < middle && values[count1] < values[count2])) {
            temp[mc] = values[count1];
            count1++;
            mc++;
        }
    
        // We copy the next value from list two.
        else {
            temp[mc] = values[count2];
            count2++;
            mc++;
        }
    }

    // Copy back all of our values into the original array.
    for (i=start; i<=end; i++)
        values[i] = temp[i - start];

    // Don't need this space any more!
    free(temp);
}