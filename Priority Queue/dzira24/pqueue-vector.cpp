/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
}

VectorPriorityQueue::~VectorPriorityQueue() {
}

int VectorPriorityQueue::size() {	
	return pqVec.size();
}

bool VectorPriorityQueue::isEmpty() {
	return pqVec.size() == 0;
}

void VectorPriorityQueue::enqueue(string value) {
	pqVec.push_back(value);
}

string VectorPriorityQueue::peek() {
	if (this->isEmpty()) {
		error("Priority Queue is empty.");
	}

	string peeked = pqVec[0];
	for (int i = 1; i < pqVec.size(); i++) {
		if (pqVec[i] < peeked)
			peeked = pqVec[i];
	}

	return peeked;
}

string VectorPriorityQueue::dequeueMin() {
	string minStr = this->peek();
	int idx = 0;
	for (int i = 0; i < pqVec.size(); i++) {
		if (pqVec[i] == minStr) idx = i;
	}
	pqVec.erase(pqVec.begin() + idx);
	
	return minStr;
}

