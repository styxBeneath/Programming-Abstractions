/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
	words = new Vector<string>();
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
	delete words;
}

int VectorPriorityQueue::size() {
	// TODO: Fill this in!
	
	return words->size();
}

bool VectorPriorityQueue::isEmpty() {
	// TODO: Fill this in!
	
	return words->size()==0;
}

void VectorPriorityQueue::enqueue(string value) {
	// TODO: Fill this in!
	words->add(value);
}
int getMinIndex(Vector<string> *words){
	int index=0;
	for (int i=1;i<words->size();i++)
		if (words->get(i)< words->get(index))
			index=i;

	return index;


}
string VectorPriorityQueue::peek() {
	// TODO: Fill this in!
	if (words->isEmpty()) error("Queue is empty");

	return words->get(getMinIndex(words));
}

string VectorPriorityQueue::dequeueMin() {
	// TODO: Fill this in!
	if (words->isEmpty()) error("Queue is empty");
	int index = getMinIndex(words);
	string value = words->get(index);
	words->remove(index);
	return value;
}

