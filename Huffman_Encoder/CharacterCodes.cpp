#include "CharacterCodes.h"



CharacterCodes::CharacterCodes(int cap)
{
	values = new char[cap];
	codes = new std::string[cap];
	numOfCodes = 0;
	capacity = cap;
}


CharacterCodes::~CharacterCodes()
{
	delete[] values;
	delete[] codes;
}

int CharacterCodes::getNumOfCodes()
{
	return numOfCodes;
}

void CharacterCodes::addCode(char v, std::string c)
{
	if (numOfCodes + 1 > capacity) {
		//TODO:throw error for capacity reached
		//or expand array
	}
	values[numOfCodes] = v;
	codes[numOfCodes] = c;
	numOfCodes++;
}

void CharacterCodes::display()
{
	for (int i = 0; i < numOfCodes; i++) {
		std::cout << values[i] << "->" << codes[i] << std::endl;
	}
}
