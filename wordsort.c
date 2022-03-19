// Alejandro Guzman Avalos
// Professor Guha - COP3502 Section 2
// Project 5 Word Sorting, Searching (Binary Search Trees)
// November 4th, 2021 - November 14th, 2021

// Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definitions

// Structures
// Used for a binary tree node.
typedef struct bintreenode {
    int data;
    struct bintreenode* left;
    struct bintreenode* right;
} btreenode;

// Used for a node in the queue.
typedef struct node {
    btreenode* nodePtr;
    struct node* next;
} node;

// Used to represent the queue efficiently.
typedef struct queue {
    node* front;
    node* back;
} queue;


// Function Prototypes
btreenode* insert(btreenode* root, int value);
int search(btreenode* root, int value);
int height(btreenode* root);
void copyToArray(btreenode* root, node* array);
void MergeSort(int values[], int start, int end);
void Merge(int values[], int start, int middle, int end);
void freeTree(btreenode* root);

// Variable Declarations
int arrIdx; 

// Main Function
int main(){

    arrIdx = 0;

	int i, j, numWords, freq;
    int actions[numWords];
    char words[numWords];

    btreenode* mytree = NULL;
	
	printf("How many words will you insert into the tree?\n");
	scanf("%d", &numWords);
    // Keeps within bounds
    if(numWords > 200000){
        printf("Number of words exceeds maximum amount\n");
        exit(0);
    }

    printf("To perform an Insertion: Type 1 and a string of 1-20 lowercase letters\n");
    printf("To perform a query: Type 2 and a string of 1-20 lowercase letters\n");
    for(i=0; i<numWords; i++){
        scanf("%d %s", &actions[i], &words[i]);
        // Keeps within bounds
        if(actions[i] != 1 || actions[i] != 2){
            printf("Invalid Input: Please type either 1 or 2.\n");
            exit(0);
        }
        // Keeps within bounds
        if(isalpha(words[i]) == 0 || strlen(&words[i]) > 20){
            printf("Please enter a lowercase alphabetical word less than 20 characters\n");
            exit(0);
        }

        mytree = insert(mytree, words[i]);
    }
        for(j=0; j<numWords; j++){
            if(words[i] == words[j]){
            freq += 1;
            }
        }
        if(freq == 0){
            printf("-1 -1\n");
        }
        else{
            printf("%d %d\n", freq, height(mytree));
            freq = 0;
        }


    // At most, 100,000 actions will be type 1
    // Height won't exceed 100

	return 0;
}

// Functions




// Inserts a new node into the tree rooted at root with data set to value.
// and returns a pointer to the root of the resulting tree.
btreenode* insert(btreenode* root, int value) {

    // Inserting into an empty tree.
    if (root == NULL) {
        btreenode* temp = malloc(sizeof(btreenode));
        temp->data = value;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }

    // Go left.
    if (value < root->data)
        root->left = insert(root->left, value);

    // Go right.
    else
        root->right = insert(root->right, value);

    // Must return the root of this tree.
    return root;
}

// Returns 1 iff value is contained in the tree pointed to be root, 0 otherwise.
int search(btreenode* root, int value) {

    // Nothing is in an empty tree.
    if (root == NULL) return 0;

    // Go left.
    if (value < root->data)
        return search(root->left, value);

    // Go right.
    else if (value > root->data)
        return search(root->right, value);

    // If we get here, we found our value!
    else
        return 1;
}

// Returns the height of the tree with root root.
int height(btreenode* root) {

    // Height of an empty tree.
    if (root == NULL) return -1;

    // Find out heights of both sides.
    int leftSide = height(root->left);
    int rightSide = height(root->right);

    // Choose the bigger one and add one.
    if (leftSide > rightSide)
        return leftSide+1;
    else
        return rightSide+1;

}

// Copy To Array
void copyToArray(btreenode* root, node* array) {

    if (root == NULL) return;

    //array[arrIdx++] = root->data; 

    copyToArray(root->left, array);

    copyToArray(root->right, array);

}

// Frees all nodes in the tree rooted at root.
void freeTree(btreenode* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
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

    // Copies the values into our auxiliary array, so long as 
    // there are numbers from both lists to copy.
    while ((count1 < middle) || (count2 <= end)) {

        // Next value to copy comes from list one - make sure list
        // one isn't exhausted yet. Also make sure we don't access index
        // count2 if we aren't supposed to.
        if (count2 > end || (count1 < middle && values[count1] < values[count2])) {
            temp[mc] = values[count1];
            count1++;
            mc++;
        }
    
        // Copies the next value from list two.
        else {
            temp[mc] = values[count2];
            count2++;
            mc++;
        }
    }

    // Copy back all of our values into the original array.
    for (i=start; i<=end; i++)
        values[i] = temp[i - start];

    // Frees the array
    free(temp);
}