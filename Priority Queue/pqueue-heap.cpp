/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include <algorithm>
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	arrSize = 100;
	queueSize = 0;
	heapArr = new string[arrSize];
}

HeapPriorityQueue::~HeapPriorityQueue() {
	delete[] heapArr;
}

int HeapPriorityQueue::size() {
	return queueSize;
}

bool HeapPriorityQueue::isEmpty() {
	return queueSize == 0;
}

// resize the heap array (makes a bigger array and replaces old one)
void HeapPriorityQueue::resize() {
	int newArrSize = arrSize * 2;
	string* newArr = new string[newArrSize];
	copy(heapArr, heapArr + arrSize, newArr);
	heapArr = newArr;
	arrSize = newArrSize;
}

void HeapPriorityQueue::enqueue(string value) {
	if (queueSize == arrSize) resize();

	heapArr[queueSize] = value;
	bubbleUp();
	queueSize++;
}

string HeapPriorityQueue::peek() {
	if (this->isEmpty())
		error("Priority queue is emty");

	return heapArr[0];
}

string HeapPriorityQueue::dequeueMin() {
	string res = this->peek();
	swap(heapArr[0], heapArr[queueSize - 1]);
	queueSize--;
	bubbleDown();

	return res;
}

// bubble down without going out of bounds
void HeapPriorityQueue::bubbleDown() {
	int currNodeIdx = 0;
	while (true) {
		int first = 2 * currNodeIdx + 1;
		int second = 2 * currNodeIdx + 2;

		bool checkFirst = first < queueSize && heapArr[currNodeIdx] > heapArr[first];
		bool checkSecond = second < queueSize && heapArr[currNodeIdx] > heapArr[second];

		if (!checkFirst && !checkSecond) break;

		if (!checkFirst && checkSecond) {
			swap(heapArr[second], heapArr[currNodeIdx]);
			currNodeIdx = second;
		} else if (checkFirst && !checkSecond) {
			swap(heapArr[first], heapArr[currNodeIdx]);
			currNodeIdx = first;
		} else {
			int i;
			if (heapArr[first] < heapArr[second]) i = first;
			else i = second;

			swap(heapArr[i], heapArr[currNodeIdx]);
			currNodeIdx = i;
		}
	}
}

// bubble up while maintaining the sort
void HeapPriorityQueue::bubbleUp() {
	int currNodeIdx = queueSize;
	int	parentNodeIdx = (queueSize - 1) / 2;
	while (parentNodeIdx != currNodeIdx && heapArr[currNodeIdx] < heapArr[parentNodeIdx]) {
		swap(heapArr[parentNodeIdx], heapArr[currNodeIdx]);
		currNodeIdx = parentNodeIdx;
		parentNodeIdx = (currNodeIdx - 1) / 2;
	}
}
