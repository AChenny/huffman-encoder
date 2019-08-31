#pragma once
template<class T, class Y>
class dictionary
{
private:
	T * words;
	Y * definitions;
	int capacity;
	int numberOfWords;
public:
	dictionary(int cap);
	~dictionary();

	
	void addToDictionary(T newItem, Y newDef);
	//RemoveFromDictionary

	//GetWord

};

