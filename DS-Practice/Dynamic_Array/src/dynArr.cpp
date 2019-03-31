#include "dynArr.h"

#include <algorithm>
#include <iostream>

using std::cout;
using std::copy;
using std::min;

template <typename T>
void dynArr<T>::push_back(T c)
{
	T* newArr = new T[maxSize + 1];

	copy(&arr[0], &arr[maxSize], newArr);
	newArr[maxSize] = c;

	delete [] arr;
	arr = newArr;
	maxSize++;
}

template <typename T>
void dynArr<T>::pop_back()
{
	T* newArr = new T[maxSize - 1];

	copy(&arr[0], &arr[maxSize - 1], newArr);
	delete [] arr;

	arr = newArr;
	maxSize--;
}
/*
template <typename T>
void dynArr<T>::emplace(size_t position, T c){
	T * newArr = new T[maxSize + 1];

	copy(&arr[0
}
*/
template <typename T>
void dynArr<T>::resize(size_t size)
{
	T* newArr = new T[size];

	copy(&arr[0], &arr[size], newArr);
	delete [] arr;

	arr = newArr;
	maxSize = size;
}

template <typename T>
void dynArr<T>::print()
{
	for(size_t i = 0; i < maxSize; i++){
		cout << arr[i] << " ";
	}
	cout << '\n';
}

template <typename T>
bool dynArr<T>::isEmpty()
{
	return (maxSize == 0) ? true : false;
}

template <typename T>
dynArr<T>::dynArr()
{
	maxSize = 0;
	arr = new T[maxSize];
}

template <typename T>
dynArr<T>::~dynArr()
{
	delete [] arr;
}

template <typename T>
const size_t dynArr<T>::size() const
{
	return maxSize;
}

template <typename T>
T& dynArr<T>::operator [] (size_t i) const
{
	return arr[i];
}

template <typename T>
const bool dynArr<T>::operator== (const dynArr<T>& arr1) const
{
	bool ret = true;
	
	size_t size = min(this->size(), arr1.size());

	for(size_t i = 0; i < size; ++i)
	{
		if (this->arr[i] != arr1[i])
		{
			ret = false;
			break;
		}
	}

	return ret;
}
