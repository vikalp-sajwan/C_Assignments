/* this program uses BST to easily create and test different cases of binary trees,
 although printColumns() fn will work for a normal binary tree also

LOGIC: 
	This is a brute force logic.
	1> first calculate the width of tree in left direction --> this will give a -ve value or zero
	2> then calculate the width of tree in right direction --> this will give a +ve value or zero
	   >>> Now we have the width of tree in both directions
	3> calculate the height of tree
	4> Now, run a nested for loop from left to right and top to bottom >> scanning the tree at every iteration.
	   At each iteration print the appropriate nodes of tree according to the value of column number and row number.
	
 
*/


#include<stdio.h>
#include<stdlib.h>

// Structure of node of the BST
typedef struct node{
	int data;
	struct node *left;
	struct node *right;
}Node;

// function to insert a node in the BST
void insertNode(Node **r, int d){
	Node *temp = (Node*)malloc(sizeof(Node));
	temp->left = temp->right = NULL;
	temp->data = d;
	
	Node *root = *r;
	
	if(root == NULL){
		*r = temp;
		return;
	}
	
	Node *pos = NULL;
	
	if( d >= root->data)
		pos = root->right;
	else
		pos = root->left;
	
	while(pos!=NULL)
	{
		root = pos;
		if(d >= pos->data)
			pos = pos->right;
		else
			pos = pos->left;
	}
	
	if( d >= root->data)
		root->right = temp;
	else
		root->left = temp;
	
}

// Print in order funtion for testing proper creation of BST
void printInOrder(Node *root){
	if(root==NULL)
		return;
	printInOrder(root->left);
	printf("%d ", root->data);
	printInOrder(root->right);
}

// recursive function to return the width of tree in positions rightwards to the root
// this will be always +ve in case where atleast one node is present at the right of root
// OR zero, if no node in tree is at right position of root 
int getRightMost(Node *root, int index){
	int left, right;
	
	if(root == NULL)
		return index;
	if(root->left != NULL)
		left = getRightMost(root->left, index-1);
	else 
		left = index;
	
	if(root->right != NULL)
		right = getRightMost(root->right, index+1);
	else 
		right = index;
		
	return (left>right)?left:right;
}

// recursive function to return the width of tree in positions leftwards to the root
// this will be always -ve in case where atleast one node is present at the left of root
// OR zero, if no node in tree is at left position of root 
int getLeftMost(Node *root, int index){
	int left, right;
	
	if(root == NULL)
		return index;
	if(root->left != NULL)
		left = getLeftMost(root->left, index-1);
	else 
		left = index;
	
	if(root->right != NULL)
		right = getLeftMost(root->right, index+1);
	else 
		right = index;
		
	return (left<right)?left:right;
}

// recursive function to calculate height of tree
int getHeight(Node *root){
	int left, right;
	left=right=0;
	
	if(root == NULL)
		return 0;
	if(root->left != NULL)
		left = getHeight(root->left);
	
	if(root->right != NULL)
		right = getHeight(root->right);

	return (left>right)?left+1:right+1;
}

// this function traverses the tree keeping track of position using currentRow and currentCol
// and prints the nodes at position colNum and rowNum
void printNodes(Node *root, int currentCol, int currentRow, int colNum, int rowNum){
	if(root == NULL)
		return;
	
	if(currentCol == colNum && currentRow == rowNum)
		printf("%d  ", root->data);
		
	if(root->left != NULL)
		printNodes(root->left, currentCol-1, currentRow+1, colNum, rowNum);
	
	if(root->right != NULL)
		printNodes(root->right, currentCol+1, currentRow+1, colNum, rowNum);
}

// this fuction is called from the main funtion
void printColumns(Node *root){
	// calculate left width -- supplying 0 because position of root is 0
	int leftmost = getLeftMost(root, 0);
	// calculate right width -- supplying 0 because position of root is 0
	int rightmost = getRightMost(root, 0);
	// calculate height
	int height = getHeight(root);
	
	int col, row;
	for(col=leftmost; col<=rightmost; col++){
		for(row=0; row<height; row++){
			// supplying 0, 0 as current position of root is 0, 0 
			// and col and row is the position of node(s) to print
			printNodes(root, 0, 0, col, row);
		}
			
	}
}

int main(){
	
	Node *root = NULL;	
	Node *root2 = NULL;	
	Node *root3 = NULL;	
	
//			2
//		  /	  \
//		1		4		
//		      /   \
//			3		5	
	insertNode(&root, 2);
	insertNode(&root, 1);
	insertNode(&root, 4);
	insertNode(&root, 3);
	insertNode(&root, 5);
	printf("expected output: 1  2  3  4  5\n");
	printf("output: ");
	printColumns(root);
	printf("\n");
	
	
//			 4
//		   /  \
//		  2	   6		
//	     / \  / \
//	    1  3 5	 7
	insertNode(&root2, 4);
	insertNode(&root2, 2);
	insertNode(&root2, 6);
	insertNode(&root2, 1);
	insertNode(&root2, 3);
	insertNode(&root2, 5);
	insertNode(&root2, 7);
	printf("expected output: 1  2  4  3  5  6  7\n");
	printf("output: ");
	printColumns(root2);
	printf("\n");
	
//			 2
//		   /  \
//		  1	    6			
//	   		  /  \
//	 		 4	  7
//		   /  \
//		  3    5	
	insertNode(&root3, 2);
	insertNode(&root3, 1);
	insertNode(&root3, 6);
	insertNode(&root3, 7);
	insertNode(&root3, 4);
	insertNode(&root3, 3);
	insertNode(&root3, 5);
	printf("expected output: 1  3  2  4  6  5  7\n");
	printf("output: ");
	printColumns(root3);
	
}
