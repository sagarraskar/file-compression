/* WORKING 
 *
 * LZW decompression works by reading index from the file, converting them into correspondig strings 
 * and writing them in the file.
 *
 * IMPLEMENTATION
 *
 * The LZW decompressor creates the same dictionary during decompression. 
 * It starts with the small table entries initialized to single characters. 
 * Then the dictionary is initialize with the small table.
 * The dictionary is updated for each character in the input stream, except the first one.
 * Decoding achieved by reading codes and translating them through the dictionary being built.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "list.h"


/* it is used to store the size of the dictionary */
short int size;

/* function to read the small table from the file */
void initdictionary(list *l){
	char ch;
	data d;
	init(l);

	while(size < 256){
		ch = size;
		
		d.str = (char*)malloc(2);
		d.str[0] = ch;
		d.str[1] = '\0';
		
		d.index = size;
		size++;

		append(l, d);
	}
}


void decompress(int fd, int fwd){
	list dictionary;
	short int old, new, len;
	char str[100], temp[100], ch;
	data d;
	
	initdictionary(&dictionary);
	//display(dictionary);
    read(fd, &old, sizeof(short int));


	strcpy(str, findstring(dictionary, old));	
	write(fwd, str, strlen(str));
	
	/* 
	 * here  variable 'new' stores the index read from the file and variable 'old' stores the previous index read from the file. 
	 * variable str is the string which is to be written in the file at the end of each loop.
	 * variable ch store the first character of the str.
	 */

	while(read(fd, &new,  sizeof(short int))){
		
		/* 
		 * if the index is not present in the table the copy the string corresponding to the previous index in str.
		 * and append the first character of the string, corresponding to the previous index to str.
		 */

		if(!search_index(dictionary, new)){
			strcpy(temp, findstring(dictionary, old));
			
			len = strlen(temp);
			
			strcpy(str, temp);
			
			str[len] = ch;
			
			str[len + 1] = '\0';
			

		}

		/*
		 * if the index is present in the table then copy the string, corresponding to the index, in the str.
		 */
		else{
			strcpy(temp, findstring(dictionary, new));

			len = strlen(temp);
		
			strcpy(str, temp);
			str[len] = '\0';
		}
	       	
		/* to write the str in the file */
		write(fwd, str, strlen(str));
	
		/* to store the first character of str in ch */
		ch = str[0];

		/* 
		 * add the new entry in the dictionary which contains
		 * d.str = string corresponding to old + first character of string corresponding to new.
		 * d.index = size;
		 */

		if(size < 4096){
			strcpy(temp, findstring(dictionary, old));
			
			len = strlen(temp);
	
			d.str = (char*)malloc(len + 2);
		
			strcpy(d.str, temp);
		
			d.str[len] = ch;
			d.str[len + 1] = '\0';


			d.index = size;
			size++;
	
			append(&dictionary, d);
		}
		
		old = new;
	}

	/* to free the dictionary */
	freelist(dictionary);
}
