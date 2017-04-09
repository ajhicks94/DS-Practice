#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class dynArr{

	private:
		T* arr;
		size_t maxSize;
	public:
		void push_back(T c);      //Add an element to the end of the array
		void pop_back();          //Remove the last element
//		void emplace(size_t position, T c);
		void resize(size_t size); //Resizes array to arr[size]
		void print();             //Print the contents of the array
		bool isEmpty();           //Check if the array is empty
		dynArr();                 //Constructor
		~dynArr();                //Destructor
};

#endif //VECTOR_H