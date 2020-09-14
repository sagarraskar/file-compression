#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
// #include "pqueue.h"

// typedef struct freqtable{
// 	char ch;
// 	int freq;
// }freqtable;

// node createnode(char *str, int freq, node* left, node* right){
//         node temp;
//         temp.data.freq = freq;
//         temp.data.str = str;
//         temp.left = left;
//         temp.right = right;
//         return temp;
// }

node create_tree(freqtable *table, int size){
        char* str;
        node *t, *left, *right;
        int freq, i = 0;
        node temp;
	pqueue q;

	/* creates the leaf nodes of the tree and add it in the priority queue */
	init(&q);
	t = (node*)malloc(sizeof(node) * size);
	while(i < size){
		t[i].data.freq = table[i].freq;
		t[i].data.str = (char*)malloc(2);
		t[i].data.str[0] = table[i].ch;
		t[i].data.str[1] = '\0';
		t[i].left = NULL;
		t[i].right = NULL;
		enqueue(&q, t[i]);
		i++;
		
	}


	/* creates the huffman tree */
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

/*function to convert character to its binary form */
char* atob(char ch){
	char *byte;
	int i = 0, rem, num = ch;
	
	byte = (char*)malloc(8);
	while(i < 8){
		byte[i] = '0';
		i++;
	}

	while(num != 0){
		rem = num % 2;
		num = num / 2;
		if(rem == 1)
			byte[i - 1] = '1';
		i--;
	}
	return byte;

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

void decompress(int fd, int fwd){
	int count, code_size, i = 0, flag = 0;;
	char ch, byte[8];
	node root, *temp;
	freqtable *table;
	
	/* reads the no of nodes */
	read(fd, &count, sizeof(int));
//	printf("%d\n", count);
	table = (freqtable*)malloc(sizeof(freqtable) * count);

	while(i < count){
		read(fd, &table[i], sizeof(freqtable));
	//	printf("%c\t", table[i].ch);
	//	printf("%d\n", table[i].freq);
		i++;
	}
	

	root = create_tree(table, count);
//	traverse(&root);
	read(fd, &ch, 1);
	strcpy(byte, atob(ch));
	i = 1;
	while(1){
		temp = &root;
		while(temp->left != NULL && temp->right != NULL){
			if(i == 8){
				if(!read(fd, &ch, 1)){
					flag = 1;	// to indicate the end of file 
					break;
				}
				strcpy(byte, atob(ch));
				i = 1;		
			}
			if(byte[i] == '0'){
				temp = temp->left;
				i++;
			}
			else if(byte[i] == '1'){
				temp = temp->right;
				i++;
			}
		}
		if(flag)
			break;
	//	printf("%c", temp->data.str[0]);
		write(fwd, &temp->data.str[0], 1);
	}

}

/*int main(int argc, char *argv[]){
	int fd, fwd;
	fd = open(argv[1], O_RDONLY);
	fwd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if(fd == -1 || fwd == -1){
		perror("Error opening file");
		return 0;
	}

	decompress(fd, fwd);
	return 0;
}*/
