#include <string>
#include "Map.h"
#include "Map.cpp"

int main() {
	std::string myString = "ABCDEF";
	Map<std::string, std::string> myDic = Map<std::string, std::string>::Map(10);

	myDic.addEntry("one", "1");
	myDic.addEntry("two", "2");
	myDic.addEntry("three", "3");
	myDic.addEntry("four", "4");

	myDic.display();

	system("PAUSE");
	return 0;
}

//Map<char, float> readData(std::string data) {
//
//}
