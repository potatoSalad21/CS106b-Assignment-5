/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	root = nullptr;
	queueSize = 0;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	while (root) {
		Node* tmp = root->next;
		delete root;
		root = tmp;
	}
}

int LinkedListPriorityQueue::size() {
	return queueSize;
}

bool LinkedListPriorityQueue::isEmpty() {
	return queueSize == 0;
}

void LinkedListPriorityQueue::enqueue(string value) {
	Node* newNode = new Node;
	newNode->val = value;
	newNode->next = nullptr;
	queueSize++;

	// simple cases
	if (queueSize == 1) {
		root = newNode;
		return;
	}
	if (root->val >= value) {
		newNode->next = root;
		root = newNode;
		return;
	}

	// inserting in the middle
	Node* tmp = root;
	while (tmp->next) {
		if (tmp->next->val >= value) {
			newNode->next = tmp->next;
			tmp->next = newNode;
			return;
		}
		tmp = tmp->next;
	}
	tmp->next = newNode;
}

string LinkedListPriorityQueue::peek() {
	if (this->isEmpty())
		error("Priority Queue is empty");
	
	return root->val;
}

string LinkedListPriorityQueue::dequeueMin() {
	if (this->isEmpty())
		error("Priority queue is empty");

	string res = root->val;
	queueSize--;
	if (this->isEmpty()) {
		delete root;
		root = nullptr;
		return res;
	}

	Node* tmp = root->next;
	delete root;
	root = tmp;

	return res;
}

