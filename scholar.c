// Alejandro Guzman ApageValos
// Professor Guha COP3502C Section 2
// Project 4: Scholar (Merge/Quick Sort)
// 10/28/21 - 10/31/21

// Included Libraries
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

// Definitions
#define MAXREAD pow(10,14)
#define MAXBOOKS pow(10,5)
#define MAXPAGES pow(10,9)

// Function Prototypes
void printArray(int values[], int length);
void inputPages(int values[], int length);
void MergeSort(int values[], int start, int end);
void Merge(int values[], int start, int middle, int end);
int calcMax(int values[], int length, int numPages, int caseValues[]);

// Main Function
int main(){
  
    int i;
    int numCases;
    long long numPages, numBooks;

    //printf("How many test cases will we be using?\n");
    scanf("%d", &numCases);
    // Keeps test cases within bounds
    if(numCases > 25){
       printf("Too many cases. Please use a number between 0 and 25");
       exit(0);
    }

    // Dynamic Allocation for Case Values
    int *caseVals;
    caseVals = (int*)(malloc(sizeof(int)*numCases));


    for(i=0; i<numCases; i++){

        //printf("How many books are in the school library, and how many pages are you willing to read?\n");
        scanf("%lld %lld", &numBooks, &numPages);

        // Checks to ensure within bounds. 
        if(numBooks > 100000 || numPages > MAXPAGES){
            printf("Either number of books or pages exceeds the max amount");
            exit(0);
        }

        // Dynamic Allocation for Page Values
        int *val;
        val = (int*)(malloc(sizeof(int)*numBooks));

        // Input the page values
        inputPages(val, numBooks);
        //printArray(val, numBooks);
    
        // Sorts the inputed values from lowest to highest
        MergeSort(val, 0, numBooks-1);
        //printArray(val, numBooks);

        // Calculate the maximum number of books you can read without going over
        // your maximum page limit. Also stores all the case max amounts in an array
        caseVals[i] = calcMax(val, numBooks, numPages, caseVals);

        // Frees the array
        free(val);
    }
    
    for(i=0; i<numCases; i++){
        printf("%d\n", caseVals[i]); 
    }

    // Frees the array
    free(caseVals);

    return 0;
}


// Functions

// inputPages
void inputPages(int values[], int length) {

    long long i;
    long long bookPages;

    for (i=0; i< length; i++){
        scanf("%lld", &bookPages);
        values[i] = bookPages;
        //printf("value in index %d is %d\n", i, values[i]);
    }
        
        // Keeps program within bounds
        if(bookPages>MAXPAGES){
            //printf("The number of pages exceeds the maximum amount");
            exit(0);
        }
}

// Print_Array
void printArray(int values[], int length) {

    long long i;
    for (i=0; i<length; i++){
        printf("%d ", values[i]);
    }
    printf("\n");
}

// Merge Sort
void MergeSort(int values[], int start, int end) {

    int mid;
  
    // Check if our sorting range is more than one element.
    if (start < end) {

        mid = (start+end)/2;
    
        // Sort the first half of the values.
        MergeSort(values, start, mid);
    
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

        // Next pageValue to copy comes from list one - make sure list
        // one isn't exhausted yet. Also make sure we don't access index
        // count2 if we aren't supposed to.
        if (count2 > end || (count1 < middle && values[count1] < values[count2])) {
            temp[mc] = values[count1];
            count1++;
            mc++;
        }
    
        // We copy the next pageValue from list two.
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

// calcMax
int calcMax(int values[], int length, int numPages, int caseValues[]){

    long long i, j;
    int sum = 0, maxAmt = 0;

    // Calculates the first sum of all amounts in the array
    for(i=0; i<length; i++){
        sum += values[i];
    }

    // Checks to see if the sum of pages exceeds the maximum number of pages you can read
    for(i=0; i<length; i++){
        if(sum > numPages){
            sum = 0;
            values[length-i] = 0;
            // Calculates the new sum 
            for(j=0; j<length; j++){
                sum += values[j];
            }
        }
    }
    // Gets the maximum amount of books the user can read without exceeding limit
    i = 0;
    while(values[i] != 0){
        maxAmt++;
        i++;
    }

    return maxAmt;

    //printf("Maximum amount of different books you can read is: %d\n", maxAmt);
    //printf("%d\n", MaxAmt);

}
