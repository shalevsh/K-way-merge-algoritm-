#include "Source.h"

int main(void) {
	char val;
	int n, k, * arr, * res;
	string fileNameInput, fileNameOutput, nString, kString;
	fstream infile, outfile;
	cin >> nString;
	n = checkValidN(nString);
	cin >> kString;
	k = checkValidK(kString, n);
	arr = new int[n];// initi the array of values
	cin >> fileNameInput;
	cin >> fileNameOutput;
	readFromInputFile(fileNameInput, arr, n);
	mergeKway(n, arr, k);
	createOutputFile(fileNameOutput, arr, n);
	delete[]arr;
}

bool checkMinus(char val) {
	if (val == '-')
		return true;
	else
		return false;
}

int checkValidN(string nString) {//check if the N is a valid number
	int i, res;
	for (i = 0; i < nString.length(); i++) {
		if (!(isNumber(nString[i]))) {
			cout << "wrong input";
			exit(1);
		}
	}
	res = stoi(nString);
	return res;
}

int checkValidK(string kString, int n) {//check if the K is a valid number
	int res;
	res = checkValidN(kString);
	if (res > n) {
		cout << "wrong input";
		exit(1);
	}
	if (res == 0) {
		cout << "wrong input";
		exit(1);
	}

	return res;
}

void mergeKway(int n, int* arr, int k) {
	int  numArrays, precision, z = 0;
	if (k == 1) {//if k =1 we do quicksort and then we finish the function
		quickSort(arr, 0, n - 1);
		return;
	}
	if (n == 1)//stop condition 
		return;
	if (n < k) {//stop condition
		quickSort(arr, 0, n - 1);
		return;
	}
	precision = n % k;
	numArrays = k;
	for (int i = 0; i < numArrays; i++) {
		if (precision) {//if we have precision we send n/k+1 intigers to the recursion
			mergeKway((n / k) + 1, (arr + (i * (n / k))) + i, k);
			precision--;
		}
		else {//else we send n/k nums to the recursion
			mergeKway(n / k, (arr + (i * (n / k))) + i - z, k);
			z++;
		}
	}
	HeapNOde** tempArr = new HeapNOde * [numArrays];//we build array that in each cell there is a class we 4 members:key,index,num of the subArray and size
	//init tempArray for the heap
	buildHelperArr(tempArr, n, k, arr);
	Heap heap(numArrays);
	heap.buildHeap(tempArr, numArrays);// build min heap
	mergeSubArraysWithHeap(n, heap, k, tempArr, arr);//here we merge the sub arryas with the min value of the heap
}




void readFromInputFile(string fileNameInput, int* arr, int n) {
	string val;
	bool haveMinus = false;
	int i, number, j = 0;
	fstream infile(fileNameInput);
	if (!infile) {
		cout << "Error with infile" << endl;
		exit(-1);
	}

	while (getline(infile, val)) {
		i = 0;
		haveMinus = checkMinus(val[0]);
		if (haveMinus)
			i++;
		for (i; i < val.length(); i++) {
			if (!(isNumber(val[i]))) {
				cout << "wrong file";
				exit(1);
			}
			number = stoi(val);
			arr[j] = number;
		}
		j++;
	}
	if (j != n) {
		cout << "wrong file";
		infile.close();
		exit(1);
	}
	infile.close();
}
void createOutputFile(string fileNameOutput, int* arr, int n) {
	ofstream outfile(fileNameOutput);
	int i;
	if (!outfile) {
		cout << "Error with outfile" << endl;
		exit(-1);
	}
	for (i = 0; i < n - 1; i++) {
		outfile << arr[i] << endl;
	}
	outfile << arr[i];
	outfile.close();
}

bool isNumber(char c) {
	return c >= '0' && c <= '9';
}
bool isEnter(char val) {
	return val == '\n';
}

int partition(int arr[], int left, int right) {
	int pivot = arr[left];
	while (left != right) {
		if (arr[left] > arr[right]) {
			swap(arr[left], arr[right]);
		}
		if (pivot == arr[left])
			right--;
		else
			left++;
	}
	return left;
}

void quickSort(int arr[], int left, int right) {
	if (left < right) {
		int index = partition(arr, left, right);
		quickSort(arr, left, index - 1);
		quickSort(arr, index + 1, right);
	}
}

void freeTempArray(HeapNOde** arr, int size) {
	for (int i = 0; i < size; i++) {
		arr[i] = nullptr;
		delete arr[i];
	}
	delete[] arr;
}

void buildHelperArr(HeapNOde** tempArr, int n, int k, int* arr) {
	int z = 0, precision, numArrays = k;
	precision = n % k;
	for (int i = 0; i < numArrays; i++) {
		tempArr[i] = new HeapNOde();// set the members values in case we have 
		if (precision) {//ערך עליון
			tempArr[i]->setKey(arr[(i * (n / k)) + i]);
			tempArr[i]->setIndex((i * (n / k)) + i);
			tempArr[i]->setTypeArr(i);
			precision--;
		}
		else {// ערך תחתון
			tempArr[i]->setKey(arr[(i * (n / k)) + i - z]);
			tempArr[i]->setIndex((i * (n / k)) + i - z);
			tempArr[i]->setTypeArr(i);
			z++;
		}
	}
	precision = n % k;//up date the sizes of each sub array(k-array)
	for (int i = 0; i < numArrays; i++) {
		if (tempArr[i]->getTypeArr() < precision)
			tempArr[i]->setSizeArr(n / k + 1);
		else
			tempArr[i]->setSizeArr(n / k);
	}
}


void mergeSubArraysWithHeap(int n, Heap heap, int k, HeapNOde** tempArr, int* arr) {
	int index, numArray, sizeK_Arr, counter = 0, numArrays = k;
	HeapNOde* nodeToInsert = nullptr, * tempMin = nullptr;
	int* res = new int[n];
	for (int i = 0; i < n; i++) {
		tempMin = heap.Min();
		res[i] = tempMin->getKey();
		if (i == n - 1) {//stop condition
			freeTempArray(tempArr, numArrays);
			delete nodeToInsert;
			memcpy(arr, res, n * sizeof(int));
			delete []res;
			return;
		}
		while (tempMin->getSizeArr() == 1) {// we "look" on each sub array from the heap

			heap.DeleteMin();
			i++;
			tempMin = heap.Min();
			res[i] = tempMin->getKey();

			if (i == n - 1) {// stop condition
				freeTempArray(tempArr, numArrays);
				delete nodeToInsert;
				memcpy(arr, res, n * sizeof(int));
				delete[] res;
				return;
			}
		}// update the next key to the next iteration
		index = tempMin->getIndex();
		numArray = tempMin->getTypeArr();
		sizeK_Arr = tempMin->getSizeArr();
		index++;
		sizeK_Arr--;
		nodeToInsert = new HeapNOde(arr[index], index, numArray, sizeK_Arr);

		tempArr[0] = nodeToInsert;
		heap.FixHeap(0);
	}
	delete nodeToInsert;
	memcpy(res, arr, n);
	delete res;
	return;
}