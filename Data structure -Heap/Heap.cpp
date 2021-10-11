#include "Heap.h"

void Heap::FixHeap(int node) {
	int min;
	int left = Left(node);
	int right = Right(node);
	
		if ((left < heapSize) && (data[left]->getKey() < data[node]->getKey()))
			min = left;
		else min = node;
	
	if ((right < heapSize) && (data[right]->getKey() < data[min]->getKey()))
		min = right;
	
	if (min != node) {
		swap(data[node], data[min]);
		FixHeap(min);
	}
}

Heap::Heap(int size) {
	data = new HeapNOde*[size];
	maxSize = size;
	heapSize = 0;
	allocated = 1;
}

Heap::Heap(HeapNOde** arr, int size) {
	buildHeap(arr, size);
}

Heap::~Heap() {
	if (allocated)
		delete[]data;
	data = nullptr;
}

void Heap::insert(HeapNOde* item) {
	if (heapSize == maxSize) {
		cout << " illegal size";
		exit(1);
	}
	int i = heapSize;
	heapSize++;
	while (i > 0 && data[Parent(i)]->getIndex() > item->getIndex()) {
		data[i] = data[Parent(i)];
		i = Parent(i);
	}
	data[i] = item;
}



void Heap::PrintHeap()
{
	for (int i = 0; i < heapSize; i++)
	{
		cout << "arr [" << i << "]" << data[i]->getKey() << " " << data[i]->getIndex() << endl;
	}


}

bool Heap::isEmpty() {
	if (data[0])
		return true;

	return false;
}

void Heap::makeEmpty() {
	for (int i = 0; i < heapSize; i++) {
		data[i] = nullptr;
	}
}

void Heap::buildHeap(HeapNOde** arr, int size)
{
	heapSize = maxSize = size;
	data = arr;
	//data = new HeapNOde *[size];
	for (int i = 0; i < size; i++) {
		
		data[i] = arr[i];
	/*	data[i]->setKey(arr[i]->getKey());
		data[i]->setIndex(arr[i]->getIndex());*/
	}
	allocated = 0;
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		FixHeap(i);
	}

}






