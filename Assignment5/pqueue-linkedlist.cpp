/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	head = new Cell;
	head->next = NULL;
	length=0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	// TODO: Fill this in!
	while (head != NULL) {
		Cell* tmpCell = head->next;
		delete head;
		head = tmpCell;
	}
}

int LinkedListPriorityQueue::size() {
	// TODO: Fill this in!
	
	return length;
}

bool LinkedListPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return length==0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	
	//case when queue is empty;
	if(length==0){
		head->value=value;
		length++;
		return;
	}

	length++;
	Cell* newCell = new Cell;
	newCell->value = value;
	
	//case when new value has the highest priority
	if(newCell->value < head->value){
		newCell->next=head;
		head=newCell;
		return;
	}
	
	// The new cell will be added betweeen these two cells
	Cell* nxt = head->next;
	Cell* prv = head;

	while (nxt != NULL) {
		if (newCell->value < nxt->value) {
			newCell->next = nxt;
			prv->next = newCell;
			return;
		}
		
		prv = nxt;
		nxt = nxt->next;
	}
	
	//case when new value is has the lowest priority
	newCell->next = NULL;
	prv->next = newCell;
}

string LinkedListPriorityQueue::peek() {
	// TODO: Fill this in!
	if (length == 0) error("Queue is empty");
	return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	string value = peek();

	//when queue contains one element
	if(length==1){
		length--;
		return value;
		
	}
	Cell* tmpCell = head;
	head = head->next;
	delete tmpCell;
	length--;
	return value;
}

