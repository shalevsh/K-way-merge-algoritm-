#pragma once
#include <iostream>
using namespace std;

class HeapNOde
{
private:
	int value;
	int index;
	int typeArr;
	int sizeArr;
public:
	HeapNOde();
	HeapNOde(int,int,int,int);
	~HeapNOde();
	int getKey()const { return value; }
	int getIndex() { return index; }
	void setKey(int newKey) { value = newKey; }
	void setIndex(int newIndex) { index = newIndex; }
	int getTypeArr()const { return typeArr; }
	int getSizeArr() { return sizeArr; }
	void setTypeArr(int _typeArr) { typeArr = _typeArr; }
	void setSizeArr(int _sizeArr) { sizeArr = _sizeArr; }
};



