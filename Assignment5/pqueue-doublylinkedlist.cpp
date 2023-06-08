/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	head = new Cell;
	tail = new Cell;
	
	//head and tail are just boundaries. they do not get any values. 
	head->next=tail;
	tail->previous=head;
	head->previous = NULL;
	tail->next = NULL;
	
	length=0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	// TODO: Fill this in!
	Cell* next = head;
	while (next != tail) {
		Cell* temp = next->next;
		delete next;
		next = temp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	// TODO: Fill this in!
	
	return length;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return length==0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	length++;
	Cell* newCell = new Cell;
	newCell->value = value;

	newCell->next = head->next;
	head->next->previous = newCell;

	head->next = newCell;
	newCell->previous = head;
}

string DoublyLinkedListPriorityQueue::peek() {
	// TODO: Fill this in!
	if(length==0) error("Queue is empty");
	Cell* temp = head->next;
	Cell* min = head->next;
	while(temp!=tail){
		if(temp->value<min->value){
			min=temp;
		}
		temp=temp->next;
	}
	return min->value;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if (size() == 0) error("Queue is Empty");

	Cell* min = head->next;
	Cell* temp = head->next->next;
	while (temp != tail) {
		if (temp->value < min->value) min = temp;
		temp = temp->next;
	}

	string result = min->value;
	min->previous->next = min->next;
	min->next->previous = min->previous;
	
	length--;
	delete min;
	return result;
}

