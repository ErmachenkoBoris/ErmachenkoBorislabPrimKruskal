#include "DHeap.h"

#define BIGNUMBER 100000;
using namespace std;

class DHeapItem
{

public: int edgeFirst, edgeSecond, weight;
	  DHeapItem(int a1, int b1, int w1) {
		  edgeFirst = a1;
		  edgeSecond = b1;
		  weight = w1;
	  }


};

class DHeap
{

private: vector<DHeapItem> store;
	   int d;
public:
	DHeap(int D) {
		d = D;
	}
	int getLeftChildIndex(int i) {
		int j = i * d + 1;
		if (j >= store.size()) {
			return -1;
		}
		else {
			return j;
		}
	}
	int getRightChildIndex(int i) {
		int j = i * d + 1;
		if (j >= store.size()) {
			return -1;
		}
		else {
			const int a = j + d - 1;
			const int b = store.size() - 1;
			return min(a, b);
		}
	}
	int getMinChildIndex(int i) {
		int leftChild = getLeftChildIndex(i);
		int rightChild = getRightChildIndex(i);
		int min = store[leftChild].weight;
		int minIndex = leftChild;
		for (int i = leftChild + 1; i <= rightChild; i++) {
			if (min < store[i].weight) {
				min = store[i].weight;
				minIndex = i;
			}
		}
		return minIndex;
	}
	int getParentIndex(int i) {
		if (i == 0) {
			return -1;
		}
		return (i - 1) % d;
	}
	void diving(int i) {
		int j1 = i;
		int j2 = getMinChildIndex(i);
		while (j2 != -1 and store[j1].weight > store[j2].weight) {
			swap(store[j1], store[j2]);
			j1 = j2;
			j2 = getMinChildIndex(j1);

		}
	}
	void emersion(int i) {
		int j1 = i;
		int j2 = getParentIndex(i);
		while (j2 != -1 and store[j1].weight > store[j2].weight) {
			swap(store[j1], store[j2]);
			j1 = j2;
			j2 = getParentIndex(j1);

		}
	}
	void decreaseKey(int i, int w) {
		store[i].weight -= w;
		emersion(i);
	}
	void increaseKey(int i, int w) {
		store[i].weight += w;
		diving(i);
	}
	void push(int a, int b, int w) {
		DHeapItem tmp(a, b, w);
		store.push_back(tmp);
		emersion(store.size() - 1);
	}
	DHeapItem pop() {
		swap(store[0], store[store.size() - 1]);
		diving(0);
		DHeapItem heapItemLast = store[store.size() - 1];
		store.pop_back();
		return heapItemLast;
	}
	void deleteItem(int i) {
		decreaseKey(i, BIGNUMBER);
		pop();
	}


};

