
// Alejandro Guzman Avalos
// Professor Guha COP3502C- Section 18
// Program 1 (Making Smoothies)
// September 8th, 2021

// Included Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
typedef struct item{
int itemID;
int numParts;
} item;

typedef struct recipe {
int numItems;
item* itemList;
int totalParts;
} recipe;

// Definitions

// Function Prototypes

char** readIngredients(int numIngredients);
recipe* readRecipe(int numItems);
recipe* readAllRecipes(int numRecipes);
double* calculateOrder(int numSmoothies, recipe** recipeList, int numIngredients);
void printOrder(char** ingredientNames, double* orderList, int numIngredients);
void freeIngredients(char** ingridientList, int numIngredients);
void freeRecipes(recipe** allRecipes, int numRecipes);

// Main
int main(){

	int numIngredients, numRecipes, numItems, numSmoothies;
	char allRecipes, recipeList;
	char* ingredientList;

	// Input number of ingredients, sends it to readIngredients
	scanf("%d", &numIngredients);
	readIngredients(numIngredients);



	// Input number of recipes, sends it to readAllRecipes and readRecipe
	scanf("%d", &numRecipes);
	readAllRecipes(numRecipes);

	// Possible error here since numItems isnt' being declared anywhere yet.
	readRecipe(numItems);

	// Input number of smoothies and stores, sends it to calculateOrder & printOrder
	scanf("%d", &numSmoothies);
	scanf("%d", &numStores);
	calculateOrder(numSmoothies, recipe** recipeList, numIngredients);


	// Frees all the dynamically allocated arrays
	freeIngredients(&ingredientList, numIngredients);
	freeRecipes(recipe** allRecipes, numRecipes);

	return 0; 
}


// Functions

// Pre-condition: 0 < numIngredients <= 100000
// Post-condition: Reads in numIngredients number of strings
//                 from standard input, allocates an array of
//                 strings to store the input, and sizes each
//                 individual string dynamically to be the
//                 proper size (string length plus 1),and 
//                 returns a pointer to the array.char** readIngredients(int numIngredients);
char** readIngredients(int numIngredients){

	int i=0; 
	char *ingredientList = (char*)malloc(sizeof(char));

	for(i=0; i<numIngredients; i++){
	scanf("%s", &ingredientList[i]);
	}
	for(i=0; i<numIngredients; i++){
	printf("%s\n", &ingredientList[i]);
	}

	return *ingredientList;
}



// Pre-condition: 0 < numItems <= 100

// Post-condition: Reads in numItems number of items
//                 from standard input for a smoothie recipe,
//                 Dynamically allocates space for a single
//                 recipe, dynamically allocates an array of
//                 item of the proper size, updates the
//                 numItems field of the struct, fills the
//                 array of items appropriately based on the 
//                 input and returns a pointer to the struct
//                 dynamically allocated.recipe* readRecipe(int numItems);

void recipe* readRecipe(int numItems){

	if(numItems <= 100){
	char*Recipe = (char*)malloc(2*sizeof(char*));





	}

}



// Pre-condition: 0 < numRecipes <= 100000

// Post-condition: Dynamically allocates an array of pointers to
//                 recipes of size numRecipes, reads numRecipes
//                 number of recipes from standard input, creates
//                 structs to store each recipe and has the 
// pointers point to each struct, in the order 
//                 the information was read in. (Should call
//                 readRecipe in a loop.)recipe** readAllRecipes(int numRecipes);
void recipe** readAllRecipes(int numRecipes){

	if(numRecipes <= 100000){
		char*Recipes = (char*)malloc(2*sizeof(char*));
		for(i=0; i<numRecipes, i++){
			readRecipe(int numItems);
		}

	}
}


// Pre-condition: 0 < numSmoothies <= 100000, recipeList is 
//    pointing to the list of allsmoothie recipes and 
//    numIngredients equals the number of total ingredients.

// Post-condition: Reads in information from standard input
//    about numSmoothies number of smoothie ordersand dynamically 
//    allocates an array of doubles of size numIngredientssuch 
//    that index i stores the # of pounds of ingredient i
//    needed to fulfill all smoothie orders andreturns a pointer 
//    to the array.double* calculateOrder(int numSmoothies, recipe** recipeList, int numIngredients);
double* calculateOrder(int numSmoothies, recipe** recipeList, int numIngredients){



	printOrder(ingredientNames, orderList, numIngredients);
}


// Pre-conditions: ingredientNames store the names of each
//                 ingredient and orderList stores the amount
//                 to order for each ingredient, and both arrays 
//                 are of size numIngredients.

// Post-condition: Prints out a list, in ingredient order, of each
//                 ingredient, a space and the amount of that
//                 ingredient to order rounded to 6 decimal
//                 places. One ingredient per line.void  printOrder(char**  ingredientNames,  double*  orderList,  int numIngredients)
void printOrder(char** ingredientNames, double* orderList, int numIngredients){

	double ingPounds;


	for(i=0; i<numStores; i++){
	storeNum = i;
	printf("Store #%d: \n", storeNum);
	printf("%s\t%.lf\n", ingredientList[i], ingPounds);
	}

	
}



// Pre-conditions: ingredientList is an array of char* of size 
//          numIngredientswith each char* dynamically allocated.

// Post-condition: all the memory pointed to by ingredientList is 
//                 freed.void freeIngredients(char** ingredientList, int numIngredients);
void freeIngredients(char** ingredientList, int numIngredients){

	for(int i=0; i<numIngredients; i++){
		free(ingredientList[i]);
	}

	free(ingredientList);
}


// Pre-conditions: allRecipes is an array of recipe* of size 
//                numRecipeswith each recipe* dynamically allocated 
//              to point to asingle recipe.

// Post-condition: all the memory pointed to by allRecipes is 
//                 freed.void freeRecipes(recipe** allRecipes, int numRecipes);
void freeRecipes(recipe** allRecipes, int numRecipes){

	for(int i=0; i<numRecipes; i++){
		free(allRecipes[i]);
	}

	free(allRecipes);

}
