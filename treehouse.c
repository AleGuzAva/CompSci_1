// Alejandro Guzman Avalos
// Professor Guha COP3502C Section 2
// Project 2: Tree House Walking
// 09/21/21 - 09/28/21

// Included Libraries
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Function Prototypes
int inputDist(testCases);
void calcDist(int x1, int y1, int x2, int y2);
float minDistance();


// Main Function
int main(){

	int testCases; 

	// Reads in how many cases will be read in 
	//printf("How many test cases will we be using today?\n");
	scanf("%d", &testCases);

	// Input distances for each test case
	inputDist(testCases);
	// Calculates number of possibilites
	calcOptions();
	// Calculates each distance AND finds the minimum
	printf("%f", minDist());

	// End of main 
	return 0;
}

// Functions


// Inputs the distances and assigns them
int inputDist(testCases){

	int i, curTree, numTrees;
	// Declares the amount of Xs and Ys necessary
	int x[numTrees+1], y[numTrees+1];

	// Loops test cases
	for(i < 0; i < testCases; i++){
		//printf("How many trees are in your backyard? (1-8)\n");
		scanf("%d", &numTrees); //DOUBLE THIS
		numTrees *= 2;
	}

	for(curTree=0; curTree < (numTrees*2); curTree++){
		//printf("What are the coordinates of Tree #%d? (x, y)", curTree);
		scanf("%d%d", x[curTree], y[curTree]);
	}
}


// Calculates how many possible ways treetops can be paired (MUST USE RECURSION)
int calcOptions(x1, y1, x2, y2){

	int x[], y[], i;
	int numOptions;

	// Base case to ensure x is within bounds.
	if(x[i] < -10000 || x[i] > 10000  || x[i+1] < -10000 || x[i+1] > 10000){
		return;
	}
	// Base case to ensure y is within bounds.
	if(y[i] < -10000 || y[i] > 10000  || y[i+1] < -10000 || y[i+1] > 10000){
		return;
	}


	// HERE IS THE RECURSION
	int i;
	for(i=0; i < numTrees; i++){
		calcOptions(x1,y1,x2,y2);
		numOptions++;
	}


	return numOptions; 
}

// Calculates the distance between trees 
void calcDist(x[numTrees+1], y[numTrees+1]){

	int i;
	// Creates an array to store values for the distance between each tree. 
	float distance[numTrees]; 

	for(i=0; i < numTrees; i++){
		distance[i] = sqrt((pow((x[i]-x[i+1]), 2)) + (pow((y[i]-y[i+1]), 2)));
		//printf("The distance between tree #%d and #%d is: %f\n", i, i+1, distance[i]);
	}	


}

// Finds the minimum distance
float minDist(){

	int i = 0;
	// minDistance set to a large number to ensure the min distance gets updated
	float minDistance = 99999999;
	float allDistances[numTrees];

	// For Loop that generates all the distances
	for(i=0; i<numTrees; i++){
		allDistances[i] = calcDist(x[numTrees], y[numTrees]);
	}

	// For Loop that finds the minimum distance
	for(i=0; i<allDistances[numTrees]; i++){
		if(allDistances[i] < minDistance){
			minDistance = allDistances[i];

		}
	}

	return minDistance;
}