#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "pqueue.h"

void init(pqueue *q){
	q->front = NULL;
	q->rear = NULL;
}

void enqueue(pqueue *q, node n){
	qnode *newnode, *temp;

	newnode = (qnode*)malloc(sizeof(qnode));
	newnode->prev = NULL;
	newnode->next = NULL;
	newnode->n = n;

	if(q->front == NULL){
		q->front = newnode;
		q->rear = newnode;
		newnode = NULL;
		return;
	}
	
	temp = q->rear;
	while(temp != NULL && (n.data.freq < temp->n.data.freq)){
		temp = temp->prev;
	}

	if(temp == NULL){
		temp = q->front;
		q->front = newnode;
		newnode->next = temp;
		temp->prev = newnode;
		newnode = NULL;
		temp = NULL;
		return;
	}

	if(temp->next == NULL){
		temp->next = newnode;
		newnode->prev = temp;
		q->rear = newnode;
		newnode = NULL;
		temp = NULL;
		return;
	}	
	newnode->next = temp->next;
	temp->next->prev = newnode;
	temp->next = newnode;
	newnode->prev = temp;

	newnode = NULL;
	temp = NULL;

}

node peek(pqueue *q){
	node n;
	n = q->front->n;
	return n;
}

node dequeue(pqueue *q){
	node n;
	qnode *temp;

	temp = q->front;

	n = q->front->n;
	q->front = temp->next;
	if(q->front == NULL){
		free(temp);
		q->rear = NULL;
		return n;
	}
	else{
		q->front->prev = NULL;
		free(temp);
		return n;
	}
}

int isempty(pqueue *q){
	if(q->front == NULL)
		return 1;
	else 
		return 0;
}

int isfull(pqueue *q){
	qnode *temp;
	temp = (qnode*)malloc(sizeof(qnode));
	if(temp == NULL)
		return 1;
	else{
		free(temp);
		return 0;
	}
}
