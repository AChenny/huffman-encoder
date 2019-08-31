#include "dictionary.h"


template <class T, class Y>
dictionary<T, Y>::dictionary(int cap)
{
	words = new T[cap];
	definitions = new Y[cap];
	capacity = cap;
	numberOfWords = 0;

}

template <class T, class Y>
dictionary<T, Y>::~dictionary()
{
}

template<class T, class Y>
void dictionary<T, Y>::addToDictionary(T newItem, Y newDef)
{
	if (numberOfWords > capacity) {
		//need to update the arrays and the capacity
		capacity = capacity * 2;
	}
	words[numberOfWords] = newItem;
	definitions[numberOfWords] = newDef;

	numberOfWords++;
}

