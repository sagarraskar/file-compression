#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

void init(list *l){
       l->size = 0;
}

void append(list *l, data d){
	l->d[l->size] = d;
	l->size++;
	
}

int search_index(list l, int index){
	if(l.d[index].index == index)
		return 1;

	return 0;
}

char* findstring(list l, int index){
	return l.d[index].str;
}

void freelist(list l){
	int i;
	while(i < l.size){
		free(l.d[i].str);
		i++;
	}

}

void display(list l){
	int i = 0;
	while(i < l.size){
		printf("%d\t%s\n", l.d[i].index, l.d[i].str);
		i++;
	}

}
