#pragma once
#include <string>
#include <iostream>
class CharacterCodes
{
private:
	char * values;
	std::string * codes;
	int numOfCodes;
	int capacity;
public:
	CharacterCodes(int);
	~CharacterCodes();
	int getNumOfCodes();
	void addCode(char v, std::string c);
	void display();
	std::string getCodeByChar(char);
	char getCharByCode(std::string);
	char getCharByIndex(int);
	std::string getValueByIndex(int);
};

