#pragma once
#include "HeapNOde.h"
#include <algorithm>    // std::swap
class Heap {
private:
	HeapNOde** data;
	int maxSize, heapSize, allocated;
	static int Left(int node) { return (2 * node + 1); }
	static int Right(int node) { return (2 * node + 2); }
	static int Parent(int node) { return (node - 1) / 2; }
	

public:
	Heap(int size);
	Heap(HeapNOde** arr, int size);
	~Heap();
	void FixHeap(int node);
	HeapNOde* Min() { return data[0]; }
	void insert(HeapNOde* item);
	HeapNOde* DeleteMin() {
		if (heapSize < 1) {
			cout << " illegal size";
			exit(1);
		}
		HeapNOde*min = Min();
		heapSize--;
		data[0] = data[heapSize];
		FixHeap(0);
		return min;
	}
	void PrintHeap();
	bool isEmpty();
	void makeEmpty();
	void buildHeap(HeapNOde** arr, int size);
	int getHeapSize() { return heapSize; }
};

