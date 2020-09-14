typedef struct data{
	int index;
	char *str;
}data;

typedef struct tnode{
	data d;
	int height;
	struct tnode *left, *right;

}tnode;

typedef struct tnode* tree;

void tinit(tree *t);


void inorder(tree t);

void preorder(tree t);

void postorder(tree t);

int height(tree t);

void insert(tree *t, data d);

int search_string(tree t, char *str);

int findindex(tree t, char *str);
