/*******************************************************************
YOU ARE NOT ALLOWED TO MODIFY THE STRUCT AND THE FUNCTION PROTOTYPES
*******************************************************************/
#ifndef STACK_HEADER
#define STACK_HEADER

#include "node.h"


typedef struct {
	int n;			//The size of the stack.
	int nCount;		//The number of elements inside the stack.
	sNode *pTop;	//POINTER pointing to the TOP of the stack. The top of the stack is the newest sNode inserted into the stack.
} stack;

//Returns a stack with size n.
stack* createStack(int n) {
	//CREATE EMPTY STACK CONTAINER
	stack* pStack = malloc(sizeof(stack));
	pStack->n = n;			//NOTE THE MAX CAPACITY
	pStack->nCount = 0;		//SET CURR ELEMS TO 0
	pStack->pTop = NULL;	//PTOP IS EMPTY NODE

	return pStack;
}

//Returns 1 if stack s is EMPTY, and 0 otherwise. The stack is empty if the value of the top pointer, pTop is NULL.
int stackEmpty(stack *s) {
	if (s->pTop == NULL){
		return 1;
	}	
	return 0;
}

//Returns 1 if stack s is FULL, and 0 otherwise. The stack is full if the number of values inside the stack is equal to n.
int stackFull(stack *s) {
	if (s->nCount == s->n){
		return 1;
	}
	return 0;
}

//Adds the new value data at the top of the stack. This moves the top pointer, pTop, to point at the newly added data. This also increments nCount by 1.
void push(stack **s, char *data) {
	if (stackFull(*s)){
		printf("\n[STACK PUSH] STACK IS FULL");
		return;
	}

	//CREATE A NEW NODE
	sNode* pNew = malloc((int)sizeof(sNode));	
	pNew->pLink = (*s)->pTop;	//LINK IT TO THE CURRENT NODE
	pNew->data = data;			//SET ITS DATA 

	//UPDATE STACK
	(*s)->pTop = pNew;	
	(*s)->nCount += 1;
}

//Returns and removes the value pointed by the top pointer of the stack, pTop. This moves the top pointer, pTop, to point to the next newest value in the stack. This also decrements nCount by 1.
char* pop(stack **s) {
	if (stackEmpty(*s)){
		printf("\n[STACK POP] STACK IS EMPTY");
		return NULL;
	}

	char* str_Extract = (*s)->pTop->data;	//TAKE THE PTOP TEXT
	(*s)->nCount -= 1;				//DECREMENT ELEMENT COUNT
	(*s)->pTop = (*s)->pTop->pLink;	//MOVE PTOP TO NEXT NODE
	
	return str_Extract;
}

//Displays the contents of the stack s following the last-in first-out (LIFO) policy.
void displayStack(stack *s) {
	while (!stackEmpty(s)){
		printf("%s ", pop(&s));
		//printf(":");
		//should it display only (use a temp) or pop it all (alter the stack)?
	}
}

//Returns, but does NOT remove, the value currently pointed by the top pointer, pTop.
char* top(stack *s) {
	if (stackEmpty(s)){
		printf("\n[STACK TOP] STACK IS EMPTY");
	}
	return s->pTop->data;
}

#endif