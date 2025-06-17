/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	root = nullptr;
	queueSize = 0;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	while (root) {
		DoubleNode* tmp = root->next;
		delete root;
		root = tmp;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	return queueSize;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	return queueSize == 0;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	DoubleNode* newNode = new DoubleNode;
	newNode->val = value;
	newNode->prev = nullptr;
	newNode->next = nullptr;
	queueSize++;

	if (!root) {
		root = newNode;
		return;
	}

	root->prev = newNode;
	newNode->next = root;
	root = newNode;
}

DoubleNode* DoublyLinkedListPriorityQueue::getMinNode() {
	if (root == nullptr)
		error("Priority Queue is empty!");

	DoubleNode* res = root;
	DoubleNode* tmp = root;
	while (tmp) {
		if (tmp->val < res->val) {
			res = tmp;
		}
		tmp = tmp->next;
	}

	return res;
}

string DoublyLinkedListPriorityQueue::peek() {
	if (this->isEmpty())
		error("Priority Queue is empty");

	return this->getMinNode()->val;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	if (this->isEmpty())
		error("Priority queue is empty");

	queueSize--;
	DoubleNode* minNode = this->getMinNode();
	string res = minNode->val;

	if (root == minNode && root->next == nullptr) {
		delete root;
		root = nullptr;

		return res;
	}

	if (minNode == root) { // minNode is the root && has children
		DoubleNode* tmp = root->next;
		delete root;
		root = tmp;
		root->prev = nullptr;

		return res;
	}

	if (minNode->next == nullptr) {
		minNode->prev->next = nullptr;
		delete minNode;

		return res;
	}

	// dequeue from middle
	minNode->prev->next = minNode->next;
	minNode->next->prev = minNode->prev;
	delete minNode;

	return res;
}

