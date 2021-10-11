#include <iostream>
#include <fstream>
#include <string>
#include "HeapNOde.h"
#include "Heap.h"
using namespace std;
bool isNumber(char c);
void readFromInputFile(string fileNameInput, int* arr, int n);
void createOutputFile(string fileNameOutput, int* arr, int n);
bool isEnter(char val);
bool checkMinus(char val);
int  checkValidN(string nString);
int  checkValidK(string kString, int n);
void mergeKway(int n, int* arr, int k);
int partition(int arr[], int left, int right);
void quickSort(int arr[], int left, int right);
void freeTempArray(HeapNOde** arr, int size);
void buildHelperArr(HeapNOde** tempArr, int n, int k, int* arr);
void mergeSubArraysWithHeap(int n, Heap heap, int k, HeapNOde** tempArr, int* arr);