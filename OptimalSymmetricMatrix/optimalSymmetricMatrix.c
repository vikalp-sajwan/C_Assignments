// in this program we are storing a symmetrix square 2-d array as 1-d array
// the crux of this implementation is the way matrix is stored as 1-d array
// and the calc_index() funtion which calculates the index in 1d array corresponding to input i and j index of 2d matrix

// the two function of assignment are defined, but not called in the program
// but it becomes obvious from the rest of the implementation that they will surely work.

#include<stdio.h>
#include<stdlib.h>

// *****#### fuction #1
int getElement(int i, int j, int *arr, int size_of_matrix){
return arr[calc_index(i, j, size_of_matrix)];
}

// *****#### fuction #2
void updateElement(int i, int j, int x, int *arr, int size_of_matrix){
arr[calc_index(i, j, size_of_matrix)] = x;
}

// funtion to calculate the index in 1d array corresponding to input i and j index of 2d matrix
// it takes index i and j and the dimention of 2-d matrix
int calc_index(int i, int j, int size_of_matrix){

if(i>j){
j=j^i;
i=j^i;
j=j^i;
}

int index = j-i;
while(i--){
index += size_of_matrix;
size_of_matrix--;
}
return index;
}

int main(){
	int i,j;
	int size_of_matrix; //dimension of square matrix
	printf("enter the size of square matrix: ");
	scanf("%d", &size_of_matrix);
	
	// the matrix will be stored in a 1-d array
	// and the number of elements in that array will be equal to no of elements in the upper triagle of matrix
	// that will be equal to SUM UPTO N NATURAL NUMBERS (therefore (size*(size+1))/2)
	int size_of_arr = (size_of_matrix * (size_of_matrix + 1)) / 2;
	
	int *arr = (int*)malloc(sizeof(int) * size_of_arr);
	
	printf("enter %d the elements of matrix(only upper triangle elements) :", size_of_arr);
	for(i=0; i<size_of_matrix; i++){
		for(j=0; j<size_of_matrix; j++){
			if(i>j)
			continue;
			scanf("%d", &arr[calc_index(i,j,size_of_matrix)]);
		}
	}
		
	printf("your matrix is:\n");
	for(i=0; i<size_of_matrix; i++){
		for(j=0; j<size_of_matrix; j++){
			printf("%d ", arr[calc_index(i,j,size_of_matrix)]);
		}
		printf("\n");
	}
}
