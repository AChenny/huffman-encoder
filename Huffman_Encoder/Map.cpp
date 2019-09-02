#include <string>
#include <iostream>
#include "Map.h"
//Todo: Convert to template
template <class T, class V>
Map<T, V>::Map(int s) {
	numEntries = 0;
	capacity = s;
	key = new T[s];
	value = new V[s];
}

//Destructor 
template<class T, class V>
Map<T, V>::~Map()
{
	//FIXME: Deleting throws an error
	//delete [] key;
	//delete [] value;
}

template<class T, class V>
int Map<T, V>::getNumEntries()
{
	return numEntries;
}

template<class T, class V>
T Map<T, V>::getKeyByIndex(int i)
{
	return key[i];
}

template<class T, class V>
V Map<T, V>::getValue(T k)
{
	for (int i = 0; i < numEntries; i++) {
		if (k == key[i]) {
			//Key found print out value
			return value[i];
		}
	}
	//Not found print out not found
	return NULL;

}

template<class T, class V>
void Map<T, V>::setValue(T k, V v)
{
	for (int i = 0; i < numEntries; i++) {
		if (k == key[i]) {
			value[i] = v;
		}
	}
}

template<class T, class V>
V Map<T, V>::getValueByIndex(int i)
{
	return value[i];
}

template<class T, class V>
void Map<T, V>::setValueByIndex(int i, V v)
{
	value[i] = v;
}

template<class T, class V>
void Map<T, V>::addEntry(T k, V v)
{
	if (numEntries + 1 > capacity) {
		//TODO: dynamically increase capacity
		std::cout << "Map full" << std::endl;
	}
	else {
		key[numEntries] = k;
		value[numEntries] = v;
		numEntries++;
	}
}

template<class T, class V>
void Map<T, V>::remove(T k)
{
	for (int i = 0; i < numEntries; i++) {
		if (k == key[i]) {
			//Key found, move everything back
			for (int j = i; j < numEntries; j++) {
				key[j] = key[j + 1];
				value[j] = value[j + 1];
			}
			numEntries--;
			return;
		}
	}
	std::cout << "Key not found" << std::endl;
}

template<class T, class V>
void Map<T, V>::display()
{
	for (int i = 0; i < numEntries; i++) {
		std::cout << key[i] << " -> " << value[i] << std::endl;
	}
}

template<class T, class V>
bool Map<T, V>::isInMap(T k)
{
	for (int i = 0; i < numEntries; i++) {
		if (k == key[i]) {
			//Key found -> return true
			return true;
		}
	}
	//Not found-> return false
	return false;
}

//int main() {
//	Map<int, std::string> m = Map<int, std::string>(10);
//	m.addEntry(1, "one");
//	m.addEntry(2, "two");
//	m.addEntry(3, "three");
//	m.addEntry(4, "four");
//	m.addEntry(5, "five");
//
//	std::cout << "---Map after added 5 elements" << std::endl;
//	m.display();
//
//	std::cout << "-----Removing 4-----" << std::endl;
//	m.remove(4);
//	m.display();
//
//	std::cout << "Search for '3': " << m.search(3) << std::endl;
//
//
//	system("PAUSE");
//	return 0;
//}