#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include <string.h>

#define max(a, b) (a) > (b)? (a) : (b)

void tinit(tree *t){
	*t = NULL;
}

/*
void inorder(tree t){
	if(t == NULL)
		return;

	inorder(t->left);

	printf("%d ", t->d.index);

	inorder(t->right);
}

void preorder(tree t){
	if(t == NULL)
		return;

	printf("%d ", t->d.index);
	
	preorder(t->left);

	preorder(t->right);
}

void postorder(tree t){
	if(t == NULL)
		return;

	postorder(t->left);

	postorder(t->right);

	printf("%d ", t->d.index);
} */

int height(tree t){
	if(t == NULL)
		return -1;
	
	return t->height;
}

void insert(tree *t, data d){
	/* function to right rotate the tree */
	tree rightRotate(tree y){
		tnode* x = y->left;
		tnode* T2 = x->right;
	
	    	/* Perform rotation */
	    	x->right = y;
	    	y->left = T2;

   	 	/* Update heights */
   	 	y->height = (max(height(y->left), height(y->right)))+1;
   	 	x->height = (max(height(x->left), height(x->right)))+1;
	
	    	return x;
	}
	
	/* function to left rotate the tree */
	tree leftRotate(tree x){
   	 	tnode* y = x->right;
   	 	tnode* T2 = y->left;
	
	    	// Perform rotation
	    	y->left = x;
	    	x->right = T2;
	
	    	//  Update heights
	    	x->height = (max(height(x->left), height(x->right))) + 1;
	    	y->height = (max(height(y->left), height(y->right))) + 1;
	
	    	// Return new root
	    	return y;
	}
	
	/* Get Balance factor of tree t */
	int getBalance(tree t){
		if (t == NULL)
	        	return 0;
    		return height(t->left) - height(t->right);
	}

	/*  Recursive function to insert a key in the subtree rooted with node and returns the new root of the subtree. */
	tree insertmain(tree t, data d){
	 	/* to perform the normal BST insertion */
		tnode *newnode;
		int key;
			
		if(t == NULL){
			newnode = (tnode*)malloc(sizeof(tnode));
			
			newnode->d = d;
			newnode->height = 0;
			newnode->left = NULL;
			newnode->right = NULL;
			
			return newnode;
		}

		key = strcmp(d.str, t->d.str);
	
		if( key < 0){
			t->left = insertmain(t->left, d);
		}
		
		else if(key > 0)
			t->right = insertmain(t->right, d);
	    
	    	else 				// Equal keys are not allowed in BST
	        	return t;



	    	/* to update the height of this ancestor node */
	
	    	t->height = 1 + (max(height(t->left), height(t->right)));
	
		
	    	/* Get the balance factor of this ancestor node to check whether this node became unbalanced */
	    	int balance = getBalance(t);
	
	    	/* If this node becomes unbalanced, then there are 4 cases */
	
	    	/* Left Left Case */
	    	if (balance > 1 && (strcmp(d.str, t->left->d.str) < 0))
	    	    return rightRotate(t);
		
	    	/* Right Right Case */
	    	if (balance < -1 && (strcmp(d.str, t->right->d.str) > 0))
	        	return leftRotate(t);
	
	    	/* Left Right Case */
		if (balance > 1 && (strcmp(d.str, t->left->d.str) > 0))
	    	{
	    	    t->left =  leftRotate(t->left);
	    	    return rightRotate(t);
	    	}
		
	    	/* Right Left Case */
	    	if (balance < -1 && (strcmp(d.str, t->right->d.str) < 0))
	    	{
	    	    t->right = rightRotate(t->right);
	    	    return leftRotate(t);
	    	}
	
	    	/* return the (unchanged) node pointer */
	    	return t;
	}

	*t = insertmain(*t, d);
}

int search_string(tree t, char* str){
	if(t == NULL)
		return 0;

	if(strcmp(str, t->d.str) < 0){
		if(search_string(t->left, str)){
			return 1;
		}
		return 0;
	
	}

	else if(strcmp(str, t->d.str) > 0){
		if(search_string(t->right, str)){
			return 1;
		}
		return 0;
	}

	else 
		return 1;


}


int findindex(tree t, char* str){
	while(t != NULL){
		if(strcmp(str, t->d.str) < 0)
			t = t->left;
		
		else if(strcmp(str, t->d.str) > 0)
			t = t->right;

		else 
			return t->d.index;
	}
	return -1;
}
