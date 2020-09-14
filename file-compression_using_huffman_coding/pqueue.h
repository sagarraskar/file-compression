typedef struct node{
    struct data{
		char *str;
		int freq;
	}data;
    struct node *left;
    struct node *right;
}node;

typedef struct qnode{
	node n;
	struct qnode *prev, *next;
}qnode;

typedef struct pqueue{
	qnode *front, *rear;
}pqueue;

void init(pqueue *p);

int isempty(pqueue *p);

int isfull(pqueue *p);

void enqueue(pqueue *p, node n);

node peek(pqueue *p);

node dequeue(pqueue *p);

