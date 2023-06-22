//This program allocated memory for an NxM integer array dynamically
//The program then prints the 2D array in a matrix form using a combination of * and [] operators
//Note: You can't use ** or [][] for printing the values (use a combination of * and [] only.

//Number of bugs/errors : 6

#include <iostream>
#include <cstdlib>
// 1. added stdio.h for printf.
#include <stdio.h>
using namespace std;

int main() {
	int N = 3, M = 5;
	int i, j;
    // 2. fixed the memory allocation.
	int**d_array = (int**) malloc( N * sizeof(int*) ); 	//Allocating memory for 2D array (N rows)
    // 3. added parenthesis for the for loop.
	for(i=0; i < N; i++) {
        d_array[i] = (int*) malloc(M * sizeof(int) );  //Allocating memory for each row with M columns)

    }
    //Initializing 2D array using [ ][ ] notation
	printf("Initializing array values!\n");
	for(i=0; i< N; i++) {			 
	     for(j=0; j < M; j++) {
             // 4. fixed the memory access.
	          *(d_array[i] + j) = i + j;
	     }
	}
	//Accessing 2D array using a combination of * and [] notation
	printf("\n");
	for(i=0; i< N; i++) {
        // 5. changed N to M to fix the loop bound.
	     for(j=0; j < M; j++) {
	          cout<<*(d_array[i]+j);
	     }
	     cout<<"\n";
	}

	//Deallocating 2D array
    // fixed deallocation.
	for(i=0; i< N; i++)			 
		free(d_array[i]);
	free(d_array);

    return 0;
}
