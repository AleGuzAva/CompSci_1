// Alejandro Guzman Avalos
// Professor Guha COP3502C Section 2
// Project 3: Winning the Lottery (Linked Lists)
// 10/03/21 - 10/10/21

// Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Structures
// Linked List Structure
struct CLL {
	int data; // PTR struct storing data
	int key;
	struct CLL *next; 
};

// Variables
struct node *next = NULL;
struct node *head = NULL; 

// Function Prototypes
void makeGroups(int totalGroups);
int lotWinner(int numPeople, int totalGroups);
struct CLL* insert_front(struct CLL * front, int num);
void freeList(struct CLL* front);



// Main Function
int main(){

struct CLL *lotteryList = NULL;

int numCases, totalGroups, num, numPeople, winGroup;

	printf("How many cases should we use?\n");
	scanf("%d", &numCases);

	printf("How many groups will we have? 1-10.\n");
	scanf("%d", &totalGroups);

	makeGroups(totalGroups);

	lotteryList = insert_front(lotteryList, num);

	freeList(lotteryList);

	printf("Lottery win is person %d from group %d.\n", lotWinner(numPeople, totalGroups), winGroup);

	return 0;
}

// Functions
// Makes the groups
void makeGroups(totalGroups){

	int i, groupNum, numPeople, skipNum, threshNum;

	for(i = 1; i<(totalGroups+1); i++){

		printf("How many people will be in group #%d?\n", i);
		scanf("%d", &numPeople);
		// Keeps values within bounds
		if(numPeople<2 || numPeople>(pow(10,5))){
			printf("Your number of people must be between 2 and 10^5!\n");
			return;
		}
		
		printf("What is the skip number for this group?\n");
		scanf("%d", &skipNum);
		// Keeps values within bounds
		if(skipNum >= numPeople){
			printf("Your skip number must be less than the number of people!\n");
			return;
		}
		
		printf("What is the threshold for this group?\n");
		scanf("%d", &threshNum);
		// Keeps values within bounds
		if(threshNum >= numPeople){
			printf("Your threshold must be less than the number of people!\n");
			return;
		}

		printf("\nGroup #%d: numPeople: %d, skipNum: %d, threshNum: %d\n", i, numPeople, skipNum, threshNum);
	}

}

// Insert Front
struct CLL* insert_front(struct CLL *front, int num) {

  struct CLL *temp, *iter;

  // Create temp node and store the value.
  temp = (struct CLL*)malloc(sizeof(struct CLL));
  temp->data = num;

  if (front == NULL) {
     temp->next = temp;
  }
  else {
     temp->next = front;
     // Iterate to the last element in the old list.
     iter = front;
     while (iter->next != front){
       iter = iter->next;
   }
     // Relink to our new first element, temp.
     iter->next = temp;
  }

  // Return the new front of the list.
  return temp;

}


// Free List
void freeList(struct CLL* front){

	// Length = 0, 1 cases.
	if (front == NULL){
		return;
	}
	if (front == front->next){
		free(front);
		return;
	}

	// Mark the front
	struct CLL* tmp = front;

	// Use tmp to delete nodes, one by one.
	tmp = tmp->next;
	while (tmp != front){
		struct CLL* del = tmp;
		tmp = tmp->next;
		free(del);
	}

	free(tmp);
}

int lotWinner(numPeople, totalGroups){
	// Lowest ID number is set to the maximum value to ensure minimum ID gets found. 
	int numID[numPeople];
	double lowestID[numPeople];
	int i, j;
	int lotWinner, min;


	for(i=0; i<numPeople; i++){
		if(numID[i] < lowestID[i]){
			min = numID[i];
		}
	}
		lowestID[i] = min;

// Finds the minimum number in each group. If two groups
// have same lowest number, lowest group wins.
	for(i=0; i<totalGroups; i++){
		for(j=0; j<totalGroups; j++){
			if(lowestID[i] < lowestID[j]){
				lotWinner = lowestID[i];
			}
		}
	}

	return lotWinner;
}
