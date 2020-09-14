#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "pqueue.h"

int count = 0, total_char = 0, least_freq;
float least_prob;

typedef struct codetable{
	char c;
	char *code;
}codetable;

typedef struct freqtable{
	char ch;
	int freq;
}freqtable;

/* function for getting fibonacci number */
int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

/* Calculating max length of Huffman code word */
int max_code_length(float p){
	int i = 0, maxcodelen;
	while((1 / p) > fib(i))
	    i++;
	

	maxcodelen = i - 3;
	return maxcodelen;
}

/* function to convert binary code to character */
char btoa(char *byte){
        int i, sum = 0;
        char ch;

        for(i = 0;i < 7 ;i++){
                sum = sum + (pow(2, i) * (byte[7 - i] - '0'));
        }
        ch = sum;
        return ch;
}

/* creates node */
node createnode(char *str, int freq, node* left, node* right){
	node temp;
	temp.data.freq = freq;
	temp.data.str = str;
	temp.left = left;
	temp.right = right;
	return temp;
}

/* Creates the Huffman tree to find the code for each character depending on its frequency */
node createtree(pqueue q){
	char* str;
	node *left, *right;
	int freq;
 	node temp;

	while(1){

		left = (node*)malloc(sizeof(node));
		right = (node*)malloc(sizeof(node));

		/* removes two nodes from the priority queue and assignes to the left and right node */
		*left = dequeue(&q);

		/* return the node if only one node is remaining in the priority queue */
		if(isempty(&q))
			return *left;	
		

		*right = dequeue(&q); 
	
		/* adds the strings in the two nodes */
		str = (char*)malloc(strlen(left->data.str) + strlen(right->data.str));
		strcpy(str, left->data.str);
		strcat(str, right->data.str);
		
		/* adds the frequency of two nodes */
		freq = left->data.freq + right->data.freq;
	
		/* creates the new node */
		temp = createnode(str, freq, left, right);

		/* inserts the new node in the priority queue */
		enqueue(&q, temp);
	}	
}

/*  reads data from input file */
node* readfile(int fd){
	node *t;
        int flag = 0, j;
	char ch;

	t = (node*)malloc(sizeof(node) * 256);
	while(read(fd, &ch, 1)){
		total_char++;
		/* checks if the character is stored already */	
		for(j = 0; j < count; j++){

			if(ch == t[j].data.str[0]){
				t[j].data.freq++;
				flag = 1; 	/* To indicate that character is already present */
				break;
			}
		}
		/* to store the character and initialies all the values if it is not stored already */
		if(!flag){
			t[count].data.str = (char*)malloc(2);
			t[count].data.str[0] = ch;
			t[count].data.str[1] = '\0';
			t[count].data.freq = 1;
			t[count].left = NULL;
			t[count].right = NULL;
			count++;
		}
		flag = 0;
	}
	return t;
}

/* creates code for each character by traversing the path in the Huffman tree */
void createcode(codetable** ptr, node* t){
	int i = 0, j = 0;
	node* temp;
	temp = t;
	if(temp->left != NULL){
		while(temp->left->data.str[i] != '\0'){
			while(1){
				if(temp->left->data.str[i] == (*ptr)[j].c){
					strcat((*ptr)[j].code, "0");
					break;
				}
				j++;
			}
			i++;
		}
		createcode(ptr, temp->left);
	}
	i = 0;
	j = 0;
	if(temp->right != NULL){
		while(temp->right->data.str[i] != '\0'){
			while(1){
			
				if(temp->right->data.str[i] == (*ptr)[j].c){
					strcat((*ptr)[j].code, "1");
					break;
				}
				j++;
			}
			i++;
		}
		createcode(ptr, temp->right);
	}
	return;

}

/* creates the decomressed file */
void createfile(codetable* ptr, int size, int fd, int fwd){
	char ch, code;
	int i = 0, j = 0, count = 1, code_size = max_code_length(least_prob);
	char byte[8];
	byte[0] = '0';
	lseek(fd, 0, SEEK_SET);
	
	while(read(fd, &ch, 1)){
		i = 0;
		while(i < size){
			
			if(ch == ptr[i].c){
				j = 0;
				while(ptr[i].code[j] != '\0'){
					if(count == 8){
						code = btoa(byte);
						write(fwd, &code, 1);
					//	printf("%s\n", byte);
						bzero(byte, 8);
						byte[0] = '0';
						count = 1;
					}
					byte[count] = ptr[i].code[j];
					count++;
					j++;
				}
				break;
			}
			i++;
		}
	}	
	if(count != 8){
	//	printf("Hi\n");
		while(count < 8){
			byte[count] = '0';
			count++;
		}
		code = btoa(byte);
		write(fwd, &code, 1);
	}
}

/*void traverse(node* temp){
        if(temp->left ==  NULL && temp->right == NULL){                 // if the node is leaf node then it prints the data in that node 
                printf("%s\t%d\n", temp->data.str, temp->data.freq);
                return;
        }

        if(temp->left != NULL)                                          // if the left child is available temp pointer points to left child and calls traverse() 
                traverse(temp->left);

        if(temp->right != NULL)                                         // if the right child is available temp pointe points to right child and calls traverse() 
                traverse(temp->right);

        return;
}*/



void compress(int fd, int fwd){
	node *t, root, n;
	pqueue q;
	int i = 0, size = 0, maxcodelen;
	codetable *ptr;
	freqtable *table;

	init(&q);
	t = readfile(fd);
/*	while(i < count){
		printf("%s\t%d\n", t[i].data.str, t[i].data.freq);
		i++;
	}*/
	/* writes the size of table in the file */
	write(fwd, &count, sizeof(int));
	table = (freqtable*)malloc(sizeof(freqtable) * count);
	i = 0;
	while(i < count){
		/* table will be  written in the compressed file and it will be used to decompressed the file */
		table[i].freq = t[i].data.freq;
		table[i].ch = t[i].data.str[0];
		write(fwd, &table[i], sizeof(table[i]));
		
		/* nodes are added into the priority queue */
		enqueue(&q, t[i]);
		i++;
	}

	n = peek(&q);

	least_freq = n.data.freq;		/* it is used to calculate the max length of huffman code */

	least_prob = (float)least_freq/total_char;
/*	printf("least_freq = %d, total_char = %d, least_prob = %f\n, fib(20) = %d, fib(21) = %d, fib(19) = %d, 1/p = %f", least_freq, total_char, least_prob, fib(20), fib(21), fib(19), 1/least_prob);*/
	root = createtree(q);

	ptr = (codetable*)malloc(sizeof(codetable) * (strlen(root.data.str)));

	while(root.data.str[size] != '\0'){
		ptr[size].c = root.data.str[size];
		size++;
	}
	i = 0;
	maxcodelen = max_code_length(least_prob);
//	printf("%d\n", maxcodelen);
	while(i < strlen(root.data.str)){
		ptr[i].code = (char*)malloc(maxcodelen);
		bzero(ptr[i].code, maxcodelen);
		i++;
	}
	createcode(&ptr, &root);


	i = 0;
/*	while(i < size){
		printf("%c\t%s\n", ptr[i].c, ptr[i].code);
		i++;
	}*/
	createfile(ptr, size, fd, fwd);

	/* to free all the dynamically alloted memory */
	free(table);
	i = 0;
	while(i < size){
		free(ptr[i].code);
		i++;
	}
	free(ptr);

	i = 0;
	while(i < count){
		free(t[i].data.str);
		i++;
	}
	free(t);
	return;
}
