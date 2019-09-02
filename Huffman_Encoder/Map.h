#pragma once

template <class T, class V>
class Map {
private:
	T * key;
	V * value;
	int numEntries;
	int capacity;

public:
	Map(int S);
	~Map();
	int getNumEntries();

	T getKeyByIndex(int);
	
	V getValue(T);
	void setValue(T, V);

	V getValueByIndex(int);
	void setValueByIndex(int, V);
	

	void addEntry(T, V);
	void remove(T);
	void display();
	
	bool isInMap(T);



};