/* WORKING
 *
 * LZW compression works by reading a sequence of symbols, grouping the symbols into strings, 
 * and converting the strings into codes. Because the codes take up less space than the strings they replace, 
 * we get compression.
 *
 * 
 * IMPLEMENTATION
 *
 * As the input data is being processed, a dictionary keeps a correspondence between the longest encountered words and a list of code values. 
 * The words are replaced by their corresponding codes and so the input file is compressed. 
 * Therefore, the efficiency of the algorithm increases as the number of long, repetitive words in the input data increases.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "tree.h"

/*  size of the dictionary */
short int size = 0;

/* function to initialize the dictionary */
void init_dictionary(tree *t){
	char ch;
    data d;
    int flag = 0, j;
	char a[256];
	bzero(a, 256);

	tinit(t);
 	
	while(size < 256){
		ch = size;
		d.str = (char*)malloc(2);
		d.str[0] = ch;
		d.str[1] = '\0';
		d.index = size;
		size++;
		insert(t, d);
	}
		
}



void compress(int fd, int fwd){
	tree dictionary;
	data d;
	short int index;
	int len;
	char p[100], pc[100], c;
	init_dictionary(&dictionary);
	pc[0] = '\0';
	p[0] = '\0';
	/* here p and pc are  strings and c is the character where pc = p + c */  
	while(read(fd, &c, 1)){
		strcpy(pc, p);
		
		len = strlen(p);
		
		pc[len] = c;
		pc[len + 1] = '\0';
		
		/* 
		 * here we check if string pc is present in the dictionary or not.
		 * if pc is not present then we add the pc into the dictionary and 
		 * write the corresponding index of string p, from the dictionary, into the compressed file.
		 * And then, p = c.
		 */

		if(!search_string(dictionary, pc)){
			if(size <= 4096){
				d.str = (char*)malloc(strlen(pc) + 1);
				strcpy(d.str, pc);
				d.str[strlen(pc)] = '\0';
				d.index = size;
			
				size++;
			
				insert(&dictionary, d);
			}
			
			index = findindex(dictionary, p);
		 	write(fwd, &index, sizeof(short int));
			
			p[0] = c;
			p[1] = '\0'; 
					
		}

		/* 
		 * if the string pc is present in the dictionary,
		 * then p = pc
		 */

		else{
			strcpy(p, pc);
			p[strlen(p)] = '\0';
		}	
	}
	
	/* to write the index of final string or char in the file */
	

	index = findindex(dictionary, p);
	write(fwd, &index, sizeof(short int));
//	freetree(&dictionary);
}
