#include <cstring>
#include <iostream>

#include "dynArr.h"

using std::cout;
using std::copy;

template <typename T>
void dynArr<T>::push_back(T c){
	T* newArr = new T[maxSize + 1];

	copy(&arr[0], &arr[maxSize], newArr);
	newArr[maxSize] = c;

	delete [] arr;
	arr = newArr;
	maxSize++;
}

template <class T>
void dynArr<T>::pop_back(){
	T* newArr = new T[maxSize - 1];

	copy(&arr[0], &arr[maxSize - 1], newArr);
	delete [] arr;

	arr = newArr;
	maxSize--;
}
/*
template <class T>
void dynArr<T>::emplace(size_t position, T c){
	T * newArr = new T[maxSize + 1];

	copy(&arr[0
}
*/
template <class T>
void dynArr<T>::resize(size_t size){
	T* newArr = new T[size];

	copy(&arr[0], &arr[size], newArr);
	delete [] arr;

	arr = newArr;
	maxSize = size;
}

template <class T>
void dynArr<T>::print(){
	for(size_t i = 0; i < maxSize; i++){
		cout << arr[i] << " ";
	}
	cout << '\n';
}

template <class T>
bool dynArr<T>::isEmpty(){
	return (maxSize == 0) ? true : false;
}

template <class T>
dynArr<T>::dynArr(){
	maxSize = 0;
	arr = new T[maxSize];
}

template <class T>
dynArr<T>::~dynArr(){
	delete [] arr;
}