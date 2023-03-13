/*******************************************************************
YOU ARE NOT ALLOWED TO MODIFY THE STRUCT AND THE FUNCTION PROTOTYPES
*******************************************************************/
#ifndef QUEUE_HEADER
#define QUEUE_HEADER

#include "node.h"

typedef struct {
	int n;        //The size of the queue.
	int nCount;   //The number of elements inside the queue.
	sNode *pHead; //Pointer pointing to the Head of the queue. The head of the queue is the oldest sNode inserted into the queue.
	sNode *pTail; //Pointer pointing to the Tail of the queue. The tail of the queue is the newest sNode inserted into the queue.
} queue;

//Returns a queue with size n.
queue* createQueue(int n) {
	queue* pQueue = malloc(sizeof(queue));
	pQueue->n = n;			//Takes note of maximum capacity of queue
	pQueue->nCount = 0;		//Initialize number of elements to 0
	pQueue->pHead = NULL;	//pHead is an empty node
	pQueue->pTail = NULL;	//pTail is an empty node

	return pQueue;
}

//Returns 1 if queue q is EMPTY, and 0 otherwise. The queue is empty if the value of both the head pointer, pHead, and the tail pointer, pHead, is NULL.
int queueEmpty(queue *q) {
	if (q->pHead == NULL && q->pTail == NULL){
		return 1;
	}	
	return 0;
}

//Returns 1 if queue q is FULL, and 0 otherwise. The queue is full if the number of values inside the queue is equal to n-1.
int queueFull(queue *q) {
	if (q->nCount == q->n-1){
		return 1;
	}
	return 0;
}

//Adds the new value data at the tail of the queue. This moves the tail pointer, pTail, to point at the newly added data. This also increments nCount by 1.
void enqueue(queue **q, char *data) {
	if (queueFull(*q)){
		printf("\n[QUEUE ENQUEUE] QUEUE IS FULL");
		return;
	}

	//Create the latest node
	sNode* pNew = malloc((int)sizeof(sNode));
	pNew->pLink = NULL;
	pNew->data = data;			//Set the data

	if(queueEmpty(*q)){
		//TAIL AND HEAD MOVE TO A FIRST VALID NODE
		(*q)->pHead = pNew;
		(*q)->pTail = pNew;
	}
	else{
		//TAIL TAKES THE LATEST NODE
		(*q)->pTail = pNew;
		
		//HEAD ATTEMPTS TO CONNECT TO THE NODE IN DIRECTION TOWARDS TAIL
		if ((*q)->pHead->pLink == NULL){
			(*q)->pHead->pLink = pNew;
		}
		else {
			sNode* pTemp = (*q)->pHead;
			for (int j = (*q)->nCount; j > 1; j--){
				pTemp = pTemp->pLink;
			}
			pTemp->pLink = pNew;
		}
	}
	(*q)->nCount += 1;  //Increment nCount by 1
}

//Returns and removes the value pointed by the head pointer of the queue, pHead. This moves the head pointer, pHead, to point to the next older value in the queue. This also decrements nCount by 1.
char* dequeue(queue **q) {
	if (queueEmpty(*q)){
		printf("\n[QUEUE DEQUEUE] QUEUE IS EMPTY");
		return NULL;
	}

	char* str_Extract = (*q)->pHead->data;	//Take pHead text
	(*q)->pHead = (*q)->pHead->pLink;	    //Move pHead to the next newer value
	(*q)->nCount -= 1;				        //Decrement nCount by 1
	
	//RESET TO STARTING NULL WHEN NO ELEMENTS ARE LEFT
	if((*q)->nCount == 0){
		(*q)->pHead = NULL;
		(*q)->pTail = NULL; 
	}

	return str_Extract;
}

//Displays the contents of the queue q following the first-in first-out (FIFO) policy.
void displayQueue(queue *q) {
	while (!queueEmpty(q)){
		printf("%s ", dequeue(&q));
	}
}

//Returns, but does NOT remove, the value currently pointed by the head pointer, pHead.
char* head(queue *q) {
	if (queueEmpty(q)){
		printf("\n[QUEUE HEAD] QUEUE IS EMPTY");
		return NULL;
	}
	return q->pHead->data;
}

//Returns, but does NOT remove, the value currently pointed by the tail pointer, pTail.
char* tail(queue *q) {
	if (queueEmpty(q)){
		printf("\n[QUEUE TAIL] QUEUE IS EMPTY");
		return NULL;
	}
	return q->pTail->data;
}

#endif