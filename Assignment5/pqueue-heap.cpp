/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	logLength = 0;
	arrLength = 10; // I took 10 as an initial size of array;
	words = new string[10];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] words;
}

int HeapPriorityQueue::size() {
	return logLength;
}

bool HeapPriorityQueue::isEmpty() {
	return size() == 0;
}

//array is dynamic, I double its size everytime it gets filled.
void enlargeArray(int& arrLength,int& logLength, string*& words) {
	arrLength = arrLength * 2;
	string* newArray = new string[arrLength];
	for (int i = 0; i < logLength; i++){
		newArray[i] = words[i];
	}
	delete[] words;
	words = newArray;
}
//if n is an odd number, its parent is n/2;
//if n is an even number, its parent is n/2 -1;
//that's because enumeration starts from 0;
void bubbleUp(int logLength, string*&words) {
	int child = logLength-1;
	int parent;
	while (child > 0) {
		
		if(child%2==1) parent = child/2;
		else parent = child/2-1;
		if (words[child]> words[parent]){
			return;
		}
		swap(words[child], words[parent]);
		child=parent;
	}
}
//if n is a parent, its childs are 2n+1 and 2n+2
//that's because enumeration starts from 0;
void bubbleDown(int logLength, string*&words) {
	int parent = 0;
	while (parent < logLength) {
		if (2*parent + 1 >= logLength){
			return;
		}
		int child = 2*parent+1;
		if (child+1 < logLength && (words[child+1] < words[child])){
			child++;
		}

		if (words[child] >= words[parent]){ 
			return;
		}

		swap(words[parent],words[child]);
		parent = child;
	}
}

void HeapPriorityQueue::enqueue(string value) {
	if (size()+1 >= arrLength){
		enlargeArray(arrLength,logLength,words);
	}
	
	words[logLength] = value;
	logLength++;
	bubbleUp(logLength,words);
}

string HeapPriorityQueue::peek() {
	if (size() == 0) error("Queue is empty");
	return words[0];
}

string HeapPriorityQueue::dequeueMin() {
	if (size() == 0) error("Queue is empty");

	string result = words[0];
	swap(words[0], words[logLength - 1]);
	logLength--;
	bubbleDown(logLength,words);

	return result;
}