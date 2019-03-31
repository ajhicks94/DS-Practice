#ifndef DYNARR_H
#define DYNARR_H

#include <stddef.h>

template <typename T>
class dynArr{
	private:
		T* arr;
		size_t maxSize;

	public:
		T& operator [] (size_t i) const;
		const bool operator== (const dynArr<T>& arr1) const;
		void push_back(T c);      //Add an element to the end of the array
		void pop_back();          //Remove the last element
//		void emplace(size_t position, T c);
		void resize(size_t size); //Resizes array to arr[size]
		void print();             //Print the contents of the array
		bool isEmpty();           //Check if the array is empty
		const size_t size() const;
		dynArr();                 //Constructor
		~dynArr();                //Destructor
};

#endif