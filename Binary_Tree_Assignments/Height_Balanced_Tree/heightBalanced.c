/*
>>> Program to check is a binary tree is Height Balanced or not.
 > A height balanced tree is one in which difference between the depths of any two leaf node is not more than 1.



this program uses BST to easily create and test different cases of binary trees,
 although isHeightBalanced() fn will work for a normal binary tree also
 
 *LOGIC -- in our recursive function we are checking if left tree is height balanced and if right tree is height balanced.
 	then the values returned ny both subtrees is checked for some conditions to decide if our current tree is height balanced or not.
 	
	A subtree can come under three catagories:
	1> height balanced with all the leaf nodes at same depth N
	2> height balanced with each leaf node at either depth N or N-1
	3> Not height balanced
	
	the values returned by above type of subtrees are:
	1> N
	2> -N  --> -ve value to indicate that it is of second type
	3> INT_MAX if tree is not height balances
	
	this causes 6 cases when root of tree is supplied in the function:
	1> root is NULL -- this will return 0, therefore empty tree is considered as a height Balanced tree
	2> either left or right subtree returns INT_MAX, therefore tree will NOT be height balanced and return INT_MAX
	3> both subtrees returns +ve values
	4> both subtrees returns -ve values
	5> left subtree returns -ve and right returns +ve
	6> right subtree returns -ve and left returns +ve
*/


#include<stdio.h>
#include<stdlib.h>
#include<limits.h>	// for the INT_MAX value used in the program

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

/*  * this recursive function 
 	* returns INT_MAX --> if the tree is NOT height balanced
 	* returns -ve int value -N --> if the tree is height balanced and all the leaf nodes are at depth N or N-1
 	* returns +ve non zero int value N --> if tree is height balanced and all the leaf nodes are at depth N
 	* returns 0 --> for an Empty Tree which is considered as height balanced in this program
 	*/
int isHeightBalanced(Node *root){
	if(root == NULL)
		return 0;
	
	int leftHeight = isHeightBalanced(root->left);
	// if left subtree is not height balanced --> return INT_MAX
	if(leftHeight == INT_MAX)
		return INT_MAX;
	
	int rightHeight = isHeightBalanced(root->right);
	// if right subtree is not height balanced --> return INT_MAX
	if(rightHeight == INT_MAX)
		return INT_MAX;
	
	// Case 3 : both subtrees return +ve heights
	if(leftHeight >= 0 && rightHeight >= 0){
		int diff = abs(leftHeight-rightHeight);
		
		//if difference between height of subtrees is greater than 1 then current tree will not be height balanced
		// therefore return INT_MAX
		if(diff > 1)
			return INT_MAX;
		// if both subtrees have same height -> return height+1
		else if(diff == 0)
			return leftHeight+1;
		// else the difference between their heights is 1
		// therefore return -VE value of (height of greater tree +1)
		else
			return (leftHeight>rightHeight) ? (-1*(leftHeight+1)) : (-1*(rightHeight+1));
	}
	
	// Case 4 : both subtrees return -ve values
	else if(leftHeight<0 && rightHeight<0){
		// as the height are -ve therefore the subtrees have already 2 possible depth of leaf nodes
		// so in this case the current tree will be Height balances only if two values are equal else NOT height balanced
		
		if(leftHeight == rightHeight)
			return leftHeight+(-1);	// the heights are -ve this time, thats why we are adding -1 to return value.
		else
			return INT_MAX;
	}
	
	// Case 5 : left subtree returns -ve and right subtree +ve
	// in this case if the height returned by right subtree is equal to either absolute value of height of left subtree
	// or 1 less than the absolute value of left subtree, then the current tree will be height balanced else NOT height Balanced
	else if(leftHeight<0){
		if(rightHeight == abs(leftHeight) || rightHeight == abs(leftHeight)-1)
			return leftHeight+(-1);	// the height is -ve, thats why we are adding -1 to return value.
		else
			return INT_MAX;
	}
	
	// Case 6 : right subtree returns -ve and left subtree +ve
	// vise versa of case 3
	else if(rightHeight<0){
		if(leftHeight == abs(rightHeight) || leftHeight == abs(rightHeight)-1)
			return rightHeight+(-1);	// the height is -ve, thats why we are adding -1 to return value.
		else
			return INT_MAX;
	}
}

int main(){
	
	Node *root = NULL;	//for first example in Question	-- height balanced
	Node *root2 = NULL;	//for second example in Question -- height balanced
	Node *root3 = NULL;	//for third example in Question -- NOT height balanced
	
//			2
//		  /	  \
//		1		4		HEIGHT BALANCED
//		      /   \
//			3		5	
	
	insertNode(&root, 2);
	insertNode(&root, 1);
	insertNode(&root, 4);
	insertNode(&root, 3);
	insertNode(&root, 5);
	printInOrder(root);
	if(isHeightBalanced(root)!=INT_MAX)
		printf("\ntree is height balanced\n");
	else 
		printf("\ntree is not height balanced\n");

//			 4
//		  /	  \
//		2	   6		HEIGHT BALANCED
//	   / \    / \
//	 1	  3	 5	 7
	insertNode(&root2, 4);
	insertNode(&root2, 2);
	insertNode(&root2, 6);
	insertNode(&root2, 1);
	insertNode(&root2, 3);
	insertNode(&root2, 5);
	insertNode(&root2, 7);
	printInOrder(root2);
	if(isHeightBalanced(root2)!=INT_MAX)
		printf("\ntree is height balanced\n");
	else 
		printf("\ntree is not height balanced\n");
	
//			 2
//		   /  \
//		 1	   6			NOT HEIGHT BALANCED
//	   		  / \
//	 		 5	 7
//			/ \
//		   3   4	
	insertNode(&root3, 2);
	insertNode(&root3, 1);
	insertNode(&root3, 6);
	insertNode(&root3, 7);
	insertNode(&root3, 5);
	insertNode(&root3, 3);
	insertNode(&root3, 4);
	printInOrder(root3);
	if(isHeightBalanced(root3)!=INT_MAX)
		printf("\ntree is height balanced\n");
	else 
		printf("\ntree is not height balanced\n");

	
}
