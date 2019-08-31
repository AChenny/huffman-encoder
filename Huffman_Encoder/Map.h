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
	void addEntry(T, V);
	void remove(T);
	void display();
	void search(T);

};