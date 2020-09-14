typedef struct data{
	short int index;
	char *str;	
}data;

typedef struct  list{
	data d[4096];
	int size;	
}list;

void init(list *l);

void append(list *l, data d);

int search_index(list l, int index);

char* findstring(list l, int index);

void freelist(list l);
	
void display(list l);

